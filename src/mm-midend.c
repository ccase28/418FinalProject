/**
 * @file mm-frontend.c
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief An interface to the custom malloc suite.
 * WARNING: Do not call malloc-dependent library functions (such as printf)
 *          from within any functions in this file. This will deadlock.
*/

#include "mm-backend.h"
#include "mm-midend.h"
#include "mm-midend-aux.h"

extern block_t *heap_start;
extern miniblock_t *miniblock_pointer;
extern block_t *seglists[];
extern size_t pagesize;

pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Initialize the heap.
 * @return true if initialization was successful
 */
static bool _mmf_init_heap(void) {
    int trylock_return;
    uint64_t *start;

    trylock_return = pthread_mutex_trylock(&global_lock);
    switch (trylock_return) {
        case 0:
        case EBUSY: // either thread gets it, or another is using
            break;
        case EINVAL:
            io_msafe_eprintf("Fatal: Uninitialized mutex.\n");
            exit(1);
        default:
            return false;
    }
    /* Lock acquired */

    // Create the initial empty heap
    if ((start = (uint64_t *)(extend_bmp(2 * wsize))) == _MM_EXTEND_BMP_FAIL)
        goto _mmf_init_heap_failure;

    start[0] = pack(0, true, true, false); // Heap prologue (block footer)
    start[1] = pack(0, true, true, false); // Heap epilogue (block header)

    /* Reset global variables */

    heap_start = (block_t *)&(start[1]);

    // Reset all size class pointers
    memset(seglists, 0, NUM_CLASSES * sizeof(void *));

    if (extend_heap(_MM_HEAP_REQUEST_CHUNKSIZE) == NULL) {
        goto _mmf_init_heap_failure;
    }

    // NOTE: 
    insert_free_block((block_t *)heap_start);

    pthread_mutex_unlock(&global_lock);
    return true;

_mmf_init_heap_failure:
    pthread_mutex_unlock(&global_lock);
    return false;
}

/**
 * @brief Extend the heap in response to allocation request.
 * @param[in] num_pages Number of pages requested by frontend
 * @return pointer to allocated payload, NULL if error occurred.
 */
void *_mm_midend_request(size_t num_pages) {
    size_t request_size, extendsize;
    block_t *block;
    void *bp = NULL;

    // Initialize heap if it isn't already
    if (heap_start == NULL) {
        _mmf_init_heap();
    }

    // Ignore spurious request
    if (num_pages == 0) {
        io_msafe_eprintf_dbg("Error: requesting 0 pages.\n");
        return bp; // NULL
    }

    pthread_mutex_lock(&global_lock);

    // Adjust block size to include overhead and to meet alignment
    // requirements
    request_size = round_up((num_pages * _MM_PAGESIZE) + wsize, SYS_MM_ALIGN);

    // Search the free list for a fit
    block = find_fit(request_size);

    // If no fit is found, request more memory, and then and place the block
    if (block == NULL) {
        // Always request at least chunksize
        extendsize = max(request_size, _MM_HEAP_REQUEST_CHUNKSIZE);
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
    split_block(block, request_size);

    bp = header_to_payload(block);

_malloc_finish:
    pthread_mutex_unlock(&global_lock);
    return bp;
}

void _mm_midend_return(void *ptr) {

    if (ptr == NULL) return;

    // cannot free if heap is uninit
    if (!heap_start) {
        io_msafe_eprintf("Fatal: cannot return on uninit heap.\n");
    }

    pthread_mutex_lock(&global_lock);
    
    block_t *block = payload_to_header(ptr);
    size_t size = get_size(block);

    if (!get_alloc(block))  {
        io_msafe_eprintf("Fatal: cannot return freed block.\n");
        exit(1);
    }

    // Mark the block as free
    bool prev_alloc = get_prev_alloc(block);
    bool prev_mini = get_prev_mini(block);
    write_block(block, size, false, prev_alloc, prev_mini);

    insert_free_block(block);

    // Try to coalesce the block with its neighbors
    coalesce_block(block);

    pthread_mutex_unlock(&global_lock);
}
