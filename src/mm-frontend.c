
#include "mm-frontend.h"
#include "mm-frontend-aux.h"


/**
 * @brief Initialize the heap.
 * @return true if initialization was successful
 */
static bool init_heap(void) {
    // Create the initial empty heap
    word_t *start = (word_t *)(extend_bmp(2 * wsize));

    if (start == (void *)-1) return false;

    start[0] = pack(0, true, true, false); // Heap prologue (block footer)
    start[1] = pack(0, true, true, false); // Heap epilogue (block header)

    /* Reset global variables */

    // Heap starts with first "block header", currently the epilogue
    heap_start = (block_t *)&(start[1]);

    chunksize = CHUNK_SIZE;

    // Initialize all size class pointers
    for (int i = 0; i < NUM_CLASSES; i++) {
        seglists[i] = NULL;
    }

    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL) {
        return false;
    }

    insert_free_block(heap_start);

    return true;
}

/**
 * @brief Extend the heap in response to allocation request.
 *
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
        init_heap();
    }

    // Ignore spurious request
    if (size == 0) {
        return bp;
    }

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
            return bp;
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
    return bp;
}

/**
 * @brief Mark an allocated region on the heap as free.
 *
 * @param[in] ptr Pointer to the start of the allocated block.
 */
void free(void *ptr) {

    if (ptr == NULL) return;

    block_t *block = payload_to_header(ptr);
    size_t size = get_size(block);

    // Mark the block as free
    bool prev_alloc = get_prev_alloc(block);
    bool prev_mini = get_prev_mini(block);
    write_block(block, size, false, prev_alloc, prev_mini);

    insert_free_block(block);

    // Try to coalesce the block with its neighbors
    coalesce_block(block);
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