/**
 * @file mm-frontend.c
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief An interface to the custom malloc suite.
 * WARNING: Do not call malloc-dependent library functions (such as printf)
 *          from within any functions in this file. This will deadlock.
 * 
 * Multiple heaps: even if we need to lock, we don't need to do so for the 
 * whole malloc/free process!
 * We can search for a suitable chunk of memory, and atomically "reserve"
 * that chunk, leading to low sync times. As long as contention on that 
 * particular block is low, CAS will likely succeed.
 * We can minimize contention by having threads keep track of where they 
 * stopped searching, and continuing searches from there every time.
*/

#include "mm-backend.h"
#include "mm-frontend.h"
#include "mm-frontend-aux.h"

// static struct {
//     // pid_t tids[_MM_INITIAL_NUM_THREADS];
//     size_t size;
//     size_t capacity;
// } _mmf_tid_hash_map = {0, _MM_INITIAL_NUM_THREADS};
static size_t _mmf_tid_hash_counter = 0;

__thread pid_t caller_tid_internal = -1;
__thread block_t *heap_start = NULL;
__thread miniblock_t *miniblock_pointer = NULL;
__thread block_t *seglists[NUM_CLASSES] = {0};
__thread size_t chunksize = CHUNK_SIZE;


/**
 * @brief Temporary function to has incoming TIDs.
*/
static pid_t _mmf_hash_tid(pid_t sys_tid) {
    (void) sys_tid;
    pid_t ret = _mmf_tid_hash_counter;
    if (++_mmf_tid_hash_counter >= _MM_INITIAL_NUM_THREADS) {
        io_msafe_eprintf(
            "FAILURE: concurrent thread count exceeds max of %d.\n",
            _MM_INITIAL_NUM_THREADS);
        errno = ENOMEM;
        return -1;
    }
    return ret;
}

/**
 * @brief Initialize the heap.
 * All heaps start out uninitialized. When a new thread calls malloc
 * for the first time, its domain heap is initialized.
 * @return true if initialization was successful
 */
static bool _mmf_init_heap(void) {
    int trylock_return;
    uint64_t *start;
    pid_t sys_tid = syscall(__NR_gettid);
    caller_tid_internal = _mmf_hash_tid(sys_tid);
    if (caller_tid_internal < 0) {
        return false; // init failure
    }
    
    // Only one thread can initialize at once
    pthread_mutex_init(&thread_arena_lock, NULL);

    trylock_return = pthread_mutex_trylock(&thread_arena_lock);
    switch (trylock_return) {
        case 0:
            break;
        case EINVAL:
            io_msafe_eprintf("Fatal: Uninitialized mutex.\n");
            exit(1);
        case EBUSY:
        default:
            return false;
    }
    /* Lock acquired */

    // Create the initial empty heap
    if ((start = (uint64_t *)(thread_extend_bmp(2 * wsize))) == _MM_EXTEND_BMP_FAIL)
        goto _mmf_init_heap_failure;

    start[0] = pack(0, true, true, false); // Heap prologue (block footer)
    start[1] = pack(0, true, true, false); // Heap epilogue (block header)

    /* Reset global variables */

    heap_start = (block_t *)&(start[1]);

    chunksize = CHUNK_SIZE;

    // Reset all size class pointers
    memset(seglists, 0, NUM_CLASSES * sizeof(void *));

    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL) {
        goto _mmf_init_heap_failure;
    }

    // NOTE: 
    insert_free_block((block_t *)heap_start);

    pthread_mutex_unlock(&thread_arena_lock);
    return true;

_mmf_init_heap_failure:
    pthread_mutex_unlock(&thread_arena_lock);
    return false;
}

/**
 * @brief Extend the heap in response to allocation request.
 * @param[in] size Amount of space requested by client
 * @return pointer to allocated payload, NULL if error occurred.
 */
void *malloc(size_t size) {
    size_t asize;      // Adjusted block size
    size_t extendsize; // Amount to extend heap if no fit is found
    block_t *block;
    void *bp = NULL;

    // Initialize heap if it isn't initialized
    // Mutex is acquired and released within this function
    if (heap_start == NULL && !_mmf_init_heap()) {
        return NULL;
    }

    // Ignore spurious request
    if (size == 0) {
        return bp; // NULL
    }

    pthread_mutex_lock(&thread_arena_lock);

    // Adjust block size to include overhead and to meet alignment
    // requirements
    asize = round_up(size + wsize, dsize);
    asize = max(asize, min_block_size);

    // Search the free list for a fit
    block = find_fit(asize);

    // If no fit is found, request more memory, and then and place the block
    if (block == NULL) {
        // Always request at least chunksize
        extendsize = max(asize, chunksize);
        block = extend_heap(extendsize);
        // extend_heap returns an error
        if (block == NULL) {
            goto _malloc_finish;
        }
    }

    // Mark block as allocated
    size_t block_size = get_size(block);

    // Remove new allocated block from free list
    remove_free_block(block);

    // Write block
    bool prev_alloc = get_prev_alloc(block);
    bool prev_mini = get_prev_mini(block);
    write_block(block, block_size, true, prev_alloc, prev_mini);

    // Try to split the block if too large
    split_block(block, asize);

    bp = header_to_payload(block);

_malloc_finish:
    pthread_mutex_unlock(&thread_arena_lock);
    return bp;
}

/**
 * @brief Mark an allocated region on the heap as free.
 *
 * @param[in] ptr Pointer to the start of the allocated block.
 */
void free(void *ptr) {

    if (ptr == NULL) return;

    // cannot free if heap is uninit
    if (!heap_start) return;

    pthread_mutex_lock(&thread_arena_lock);

    // Should we make provisions for multiple threads freeing?
    
    block_t *block = payload_to_header(ptr);
    size_t size = get_size(block);

    if (!get_alloc(block)) {
        io_msafe_eprintf("Fatal: free called on freed block.\n");
    };

    // Mark the block as free
    bool prev_alloc = get_prev_alloc(block);
    bool prev_mini = get_prev_mini(block);
    write_block(block, size, false, prev_alloc, prev_mini);

    insert_free_block(block);

    // Try to coalesce the block with its neighbors
    coalesce_block(block);

    pthread_mutex_unlock(&thread_arena_lock);
}

/**
 * @brief Move a specified amount of memory from previously allocated area
 * to a new location in memory.
 * If size of destination is greater, extra blocks are not initialized.
 *
 * @param[in] ptr Pointer to a block in the heap.
 * @param[in] size The size of the destination block.
 * @return A pointer to the newly allocated block.
 */
void *realloc(void *ptr, size_t size) {
    block_t *block = payload_to_header(ptr);
    size_t copysize;
    void *newptr;

    // If size == 0, then free block and return NULL
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // If ptr is NULL, then equivalent to malloc
    if (ptr == NULL) {
        return malloc(size);
    }

    // Otherwise, proceed with reallocation
    newptr = malloc(size);

    // If malloc fails, the original block is left untouched
    if (newptr == NULL) {
        return NULL;
    }

    // Copy the old data
    copysize = get_payload_size(block); // gets size of old payload
    if (size < copysize) {
        copysize = size;
    }
    memcpy(newptr, ptr, copysize);

    // Free the old block
    free(ptr);

    return newptr;
}

/**
 * @brief Allocate an array of elements onto the heap and initialize all
 * contents to zero.
 *
 * @param[in] nmemb The number of elements in the array.
 * @param[in] size The size of each element in the array.
 * @return A pointer to the new allocated array.
 */
void *calloc(size_t nmemb, size_t size) {
    void *ptr;
    size_t asize = nmemb * size;

    if (nmemb == 0) {
        return NULL;
    }
    if (asize / nmemb != size) {
        // Multiplication overflowed
        return NULL;
    }

    ptr = malloc(asize);
    if (ptr == NULL) {
        return NULL;
    }

    // Initialize all bits to 0
    memset(ptr, 0, asize);

    return ptr;
}