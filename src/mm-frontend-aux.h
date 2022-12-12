#ifndef _MM_FRONTEND_AUX_H
#define _MM_FRONTEND_AUX_H

#include "mm-comm.h"

/** @brief Number of samples in average block size estimation */
#define NUM_ITERS 100

/** @brief Minimum size by which the heap extends (1 page min.) */
#define CHUNK_SIZE (1 << 12)

typedef uint64_t word_t;

/** @brief Represents the header and payload of one block in the heap */
struct block {
    /**
     * @brief Header contains size + allocation flag
     */
    word_t header;
    union {
        struct {
            struct block *prev;
            struct block *next;
        } ptrs;
        char payload[0];
    };
};

/** @brief Represents a fixed-size miniblock in the heap */
struct miniblock {
    word_t header;
    union {
        struct miniblock *next;
        char payload[0];
    };
};

/* Basic constants */

/** @brief Word and header size (bytes) */
static const size_t wsize = sizeof(word_t);

/** @brief Double word size (bytes) */
static const size_t dsize = 2 * wsize;

/** @brief Minimum block size (bytes) */
static const size_t min_block_size = dsize;

/** @brief Mask that indicates the allocated bit in header */
static const word_t alloc_mask = 0x1;

/** @brief Mask that indicates size of block in header */
static const word_t size_mask = ~(word_t)0xF;

/** @brief Mask that indicates the allocation status of previous block */
static const word_t prev_alloc_mask = 0x2;

/** @brief Mask that indicates whether the previous consecutive block
 * is a miniblock */
static const word_t prev_mini_mask = 0x4;

/** @brief How far to search seglists for desired block for best fit policy */
static const size_t search_depth = 18;

/** @brief Set of size classes for segregated list */
static const size_t size_classes[] = {16, 48, 64, 80, 96, 128, 256, 1024, 4096, 8192};

/**
 * @brief Returns the maximum of two integers.
 * @param[in] x
 * @param[in] y
 * @return `x` if `x > y`, and `y` otherwise.
 */
size_t max(size_t x, size_t y);

/**
 * @brief Rounds `size` up to next multiple of n
 * @param[in] size
 * @param[in] n
 * @return The size after rounding up
 */
size_t round_up(size_t size, size_t n);

/**
 * @brief Packs the `size` and `alloc` of a block into a word suitable for
 *        use as a packed value.
 *
 * Packed values are used for both headers and footers.
 *
 * The allocation status is packed into the lowest bit of the word.
 *
 * @param[in] size The size of the block being represented
 * @param[in] alloc True if the block is allocated
 * @return The packed value
 */
word_t pack(size_t size, bool alloc, bool palloc, bool pmini);

/**
 * @brief Extracts the size represented in a packed word.
 *
 * This function simply clears the lowest 4 bits of the word, as the heap
 * is 16-byte aligned.
 *
 * @param[in] word
 * @return The size of the block represented by the word
 */
size_t extract_size(word_t word);

/**
 * @brief Extracts the size of a block from its header.
 * @param[in] block
 * @return The size of the block
 */
size_t get_size(block_t *block);

/**
 * @brief Extracts the alloc of a block from its header.
 * @param[in] block
 * @return The alloc of the block
 */
bool get_alloc(block_t *block);

/**
 * @brief Return whether the previous block is a miniblock.
 * @param[in] block A block in the heap.
 * @return whether the previous block is a miniblock.
 */
bool get_prev_mini(block_t *block);

/**
 * @brief Returns the allocation status of the previous block.
 * @param[in] block
 * @return The allocation status of the previous block
 */
bool get_prev_alloc(block_t *block);

/**
 * @brief Given a payload pointer, returns a pointer to the corresponding
 *        block.
 * @param[in] bp A pointer to a block's payload
 * @return The corresponding block
 */
block_t *payload_to_header(void *bp);

/**
 * @brief Given a block pointer, returns a pointer to the corresponding
 *        payload.
 * @param[in] block
 * @return A pointer to the block's payload
 * @pre The block must be a valid block, not a boundary tag.
 */
void *header_to_payload(block_t *block);

/**
 * @brief Given a block pointer, returns a pointer to the corresponding
 *        footer.
 * @param[in] block
 * @return A pointer to the block's footer
 * @pre The block must be a valid block, not a boundary tag.
 */
word_t *header_to_footer(block_t *block);

/**
 * @brief Given a block footer, returns a pointer to the corresponding
 *        header.
 * @param[in] footer A pointer to the block's footer
 * @return A pointer to the start of the block
 * @pre The footer must be the footer of a valid block, not a boundary tag.
 */
block_t *footer_to_header(word_t *footer);

/**
 * @brief Returns the payload size of a given block.
 *
 * The payload size is equal to the entire block size minus the sizes of the
 * block's header and footer.
 *
 * @param[in] block
 * @return The size of the block's payload
 */
size_t get_payload_size(block_t *block);

/**
 * @brief Writes a block starting at the given address.
 *
 * This function writes both a header and footer, where the location of the
 * footer is computed in relation to the header.
 *
 * @param[out] block The location to begin writing the block header
 * @param[in] size The size of the new block
 * @param[in] alloc The allocation status of the new block
 */
void write_block(block_t *block, size_t size, bool alloc, bool palloc,
                        bool pmini);

/**
 * @brief Find the size class of a block size.
*/
short find_size_class(size_t size);

/**
 * @brief Find the epilogue of the current heap.
 * @return a pointer to the epilogue.
*/
block_t *find_epilogue();

/**
 * @brief Insert a free block into the free list.
 *
 * Insert the block into the smallest size class in which it fits.
 *
 * @param[in] The block to be inserted.
 */
void insert_free_block(block_t *block);

/**
 * @brief Remove the indicated block from the free list.
 * Given a block, search the seglist for the list that contains that block
 * and remove block from that list.
 *
 * @param[in] block The block to be removed.
 */
void remove_free_block(block_t *block);

/**
 * @brief Given a free block, coalesce the block with its neighbors.
 *
 * Remove the block along with each free neighbor from the free list and
 * write a new free block with the size of the sum of each of the free blocks,
 * and add that block to the free list.
 *
 * @param[in] block The block to be coalesced.
 * @return A pointer to the newly coalesced block.
 */
block_t *coalesce_block(block_t *block);

/**
 * @brief Extend the heap by a given number of bytes.
 *
 * @param[in] size The number of bytes to extend the heap by
 *
 * @return A pointer to the first free block of the newly extended heap
 */
block_t *extend_heap(size_t size);

/**
 * @brief Split an allocated block into allocated and free segments
 *
 * @param[in] block The block to split
 * @param[in] asize The size of the allocated segment of the block
 */
void split_block(block_t *block, size_t asize);

/**
 * @brief Find a free block for a given block size.
 *
 * @param[in] asize The minimum size of the free block to be returned
 * @return A pointer to an appropriate free block on the heap, or
 * NULL if there is none
 */
block_t *find_fit(size_t asize);

#endif /* _MM_FRONTEND_H */