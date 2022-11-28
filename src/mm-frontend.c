/**
 * @file mm-frontend.c
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief An interface to the custom malloc suite.
 * WARNING: Do not call malloc-dependent library functions (such as printf)
 *          from within any functions in this file. This will deadlock.
*/

#include "mm-backend.h"
#include "mm-frontend.h"
#include "mm-frontend-aux.h"

extern volatile block_t *heap_start;
extern volatile miniblock_t *miniblock_pointer;
extern volatile block_t *seglists[];
extern size_t chunksize;

pthread_mutex_t *global_lock_addr = NULL;
__thread pthread_mutex_t local_initializer;


static void _mmf_cas_lock_finalize(void **__restrict__ addr, void *__restrict__ const src) {
    __asm__ (
        "xorq %rax, %rax\n\t"
        "lock cmpxchgq %rsi, (%rdi)\n\t");
}

/**
 * @brief Initialize the heap.
 * @return true if initialization was successful
 */
static bool _mmf_init_heap(void) {
    uint64_t *start;
    // Only one thread can initialize at once
    pthread_mutex_init(&local_initializer, NULL);
    _mmf_cas_lock_finalize((void **)&global_lock_addr, (void *)&local_initializer);

    // Create the initial empty heap
    if ((start = (uint64_t *)(extend_bmp(2 * wsize))) == _MM_EXTEND_BMP_FAIL)
        return false;

    start[0] = pack(0, true, true, false); // Heap prologue (block footer)
    start[1] = pack(0, true, true, false); // Heap epilogue (block header)

    /* Reset global variables */

    heap_start = (block_t *)&(start[1]);

    chunksize = CHUNK_SIZE;

    // Reset all size class pointers
    memset(seglists, 0, NUM_CLASSES * sizeof(void *));

    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL) {
        return false;
    }

    insert_free_block(heap_start);

    return true;
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
    if (heap_start == NULL) {
        _mmf_init_heap();
    }

    // Ignore spurious request
    if (size == 0) {
        return bp; // NULL
    }

    pthread_mutex_lock(global_lock_addr);

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
    pthread_mutex_unlock(global_lock_addr);
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
    if (!heap_start || !global_lock_addr) return;

    pthread_mutex_lock(global_lock_addr);

    // Should we make provisions for multiple threads freeing?
    
    block_t *block = payload_to_header(ptr);
    size_t size = get_size(block);

    if (get_alloc(block)) exit(1);

    // Mark the block as free
    bool prev_alloc = get_prev_alloc(block);
    bool prev_mini = get_prev_mini(block);
    write_block(block, size, false, prev_alloc, prev_mini);

    insert_free_block(block);

    // Try to coalesce the block with its neighbors
    coalesce_block(block);

    pthread_mutex_unlock(global_lock_addr);
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