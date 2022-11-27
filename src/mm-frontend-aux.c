/**
 * @file mm-frontend-aux.c
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief Auxiliary functions for allocator frontend.
*/

#include "mm-frontend-aux.h"
#include "mm-backend.h"

/**
 * @brief Returns the maximum of two integers.
 * @param[in] x
 * @param[in] y
 * @return `x` if `x > y`, and `y` otherwise.
 */
size_t max(size_t x, size_t y) {
    return (x > y) ? x : y;
}

/**
 * @brief Rounds `size` up to next multiple of n
 * @param[in] size
 * @param[in] n
 * @return The size after rounding up
 */
size_t round_up(size_t size, size_t n) {
    return n * ((size + (n - 1)) / n);
}

static block_t *find_prev_free(block_t *block) {

    block_t *prev = (block->ptrs).prev;
    return prev;
}

static block_t *find_next_free(block_t *block) {

    block_t *nxt = (block->ptrs).next;
    return nxt;
}

static void set_prev_free(block_t *block, block_t *new_prev) {
    (block->ptrs).prev = new_prev;
}

static void set_next_free(block_t *block, block_t *new_next) {
    (block->ptrs).next = new_next;
}

static void set_prev_alloc(block_t *block, bool alloc) {

    if (alloc) {
        block->header |= prev_alloc_mask;
    } else {
        block->header &= ~prev_alloc_mask;
    }
}

word_t pack(size_t size, bool alloc, bool palloc, bool pmini) {
    word_t word = size;
    if (alloc) {
        word |= alloc_mask;
    }
    if (palloc) {
        word |= prev_alloc_mask;
    }
    if (pmini) {
        word |= prev_mini_mask;
    }
    return word;
}

size_t extract_size(word_t word) {
    return (word & size_mask);
}

size_t get_size(block_t *block) {
    return extract_size(block->header);
}

block_t *payload_to_header(void *bp) {
    return (block_t *)((char *)bp - offsetof(block_t, payload));
}

void *header_to_payload(block_t *block) {
    return (void *)(block->payload);
}

word_t *header_to_footer(block_t *block) {
    return (word_t *)(block->payload + get_size(block) - dsize);
}


block_t *footer_to_header(word_t *footer) {
    size_t size = extract_size(*footer);
    return (block_t *)((char *)footer + wsize - size);
}

size_t get_payload_size(block_t *block) {
    size_t asize = get_size(block);
    return asize - wsize;
}

static bool extract_alloc(word_t word) {
    return (bool)(word & alloc_mask);
}

static bool get_alloc(block_t *block) {
    return extract_alloc(block->header);
}

static bool extract_prev_alloc(word_t word) {
    return (bool)(word & prev_alloc_mask);
}

bool get_prev_alloc(block_t *block) {
    return extract_prev_alloc(block->header);
}

static void write_epilogue(block_t *block) {
    block->header = pack(0, true, false, false);
}

static bool is_miniblock(block_t *block) {
    return get_size(block) <= 16;
}

static block_t *find_next(block_t *block) {
    return (block_t *)((char *)block + get_size(block));
}

bool get_prev_mini(block_t *block) {
    return (bool)(block->header & prev_mini_mask);
}

static void set_prev_mini(block_t *block, bool is_prev_mini) {
    if (is_prev_mini) {
        block->header |= prev_mini_mask;
    } else {
        block->header &= ~prev_mini_mask;
    }
}

void write_block(block_t *block, size_t size, bool alloc, bool palloc,
                        bool pmini) {

    block->header = pack(size, alloc, palloc, pmini);

    // Write footer for regular free blocks
    if (!alloc) {
        if (size > min_block_size) {
            word_t *footerp = header_to_footer(block);
            *footerp = pack(size, alloc, palloc, pmini);
        }
    }

    block_t *nxt = find_next(block);
    set_prev_alloc(nxt, alloc);
    set_prev_mini(nxt, (size <= min_block_size));
}

static word_t *find_prev_footer(block_t *block) {
    // Compute previous footer position as one word before the header
    return &(block->header) - 1;
}

static block_t *find_prev(block_t *block) {

    if (get_prev_mini(block)) {
        return (block_t *)((char *)block - min_block_size);
    }

    word_t *footerp = find_prev_footer(block);

    // Return NULL if called on first block in the heap
    if (extract_size(*footerp) == 0) {
        return NULL;
    }

    return footer_to_header(footerp);
}

short find_size_class(size_t size) {
    for (short i = 0; i < NUM_CLASSES; i++) {
        if (i == NUM_CLASSES - 1 ||
            (size >= size_classes[i] && size < size_classes[i + 1])) {
            return i;
        }
    }
    assert(false);
    return 0;
}

block_t *find_epilogue() {
    return (block_t *)((char *)mem_heap_hi() - 7);
}

void insert_free_block(block_t *block) {

    if (is_miniblock(block)) {
        miniblock_t *mb = (miniblock_t *)block;
        mb->next = miniblock_pointer;
        miniblock_pointer = mb;
        return;
    }

    short sc = find_size_class(get_size(block));
    block_t *sc_pointer = seglists[sc];

    if (sc_pointer == NULL) {
        sc_pointer = block;
        set_prev_free(sc_pointer, sc_pointer);
        set_next_free(sc_pointer, sc_pointer);

        // Update root pointer in size class array
        seglists[sc] = sc_pointer;
    } else {
        block_t *next = find_next_free(sc_pointer);

        set_prev_free(block, sc_pointer);
        set_next_free(sc_pointer, block);
        set_prev_free(next, block);
        set_next_free(block, next);
    }
}

void remove_free_block(block_t *block) {

    if (is_miniblock(block)) {
        if (block == (block_t *)miniblock_pointer) {
            miniblock_pointer = (miniblock_pointer->next);
        } else {
            miniblock_t *mb = miniblock_pointer;
            while (mb != NULL && mb->next != NULL) {
                if (mb->next == (miniblock_t *)block) {
                    mb->next = mb->next->next;
                    return;
                }
                mb = mb->next;
            }
        }
        return;
    }

    // Get parent free list
    short sc = find_size_class(get_size(block));
    block_t *sc_pointer = seglists[sc];

    block_t *prev = find_prev_free(block);
    block_t *next = find_next_free(block);

    if (prev == block) {

        // If block is the only block in list, remove it
        seglists[sc] = NULL;
    } else {
        if (block == sc_pointer) {
            // if root is removed, move pointer backward in list
            seglists[sc] = prev;
        }
        set_prev_free(next, prev);
        set_next_free(prev, next);
    }
}

block_t *coalesce_block(block_t *block) {

    bool prev_alloc = get_prev_alloc(block);

    size_t prev_size;
    if (get_prev_mini(block)) {
        prev_size = min_block_size;
    } else {
        prev_size = extract_size(*(find_prev_footer(block)));
    }

    bool next_alloc = get_alloc(find_next(block));
    size_t next_size = get_size(find_next(block));

    size_t cur_size = get_size(block);

    /* Case 1 */
    if (prev_alloc && next_alloc) {
        return block;
    }

    /* Case 2 */
    else if (prev_alloc && !next_alloc) {
        // Remove coalescing block from list
        remove_free_block(find_next(block));
        remove_free_block(block);

        // Write new coalesced block
        bool cur_prev_mini = get_prev_mini(block);
        write_block(block, cur_size + next_size, false, true, cur_prev_mini);

        insert_free_block(block);
        return block;
    }

    /* Case 3 */
    else if (!prev_alloc && next_alloc) {
        block_t *prev = find_prev(block);
        bool pp_alloc = get_prev_alloc(prev);
        bool pp_mini = get_prev_mini(prev);
        remove_free_block(prev);
        remove_free_block(block);
        write_block(prev, prev_size + cur_size, false, pp_alloc, pp_mini);

        insert_free_block(prev);
        return prev;
    }

    /* Case 4 */
    else if (!prev_alloc && !next_alloc) {
        block_t *prev = find_prev(block);
        bool pp_alloc = get_prev_alloc(prev);
        bool pp_mini = get_prev_mini(prev);
        remove_free_block(prev);
        remove_free_block(find_next(block));
        remove_free_block(block);
        write_block(prev, prev_size + cur_size + next_size, false, pp_alloc,
                    pp_mini);

        insert_free_block(prev);
        return prev;
    }
    return NULL;
}

block_t *extend_heap(size_t size) {
    void *bp;

    bool prev_block_alloc = get_prev_alloc(find_epilogue());
    bool prev_block_mini = get_prev_mini(find_epilogue());

    // Allocate an even number of words to maintain alignment
    size = round_up(size, dsize);
    if ((bp = extend_bmp((intptr_t)size)) == (void *)-1) {
        return NULL;
    }

    // Initialize free block header/footer
    block_t *block = payload_to_header(bp);

    write_block(block, size, false, prev_block_alloc, prev_block_mini);

    // Add new free block to free list
    insert_free_block(block);

    // Create new epilogue header
    block_t *block_next = find_next(block);
    write_epilogue(block_next);

    // Coalesce in case the previous block was free
    block = coalesce_block(block);

    return block;
}

void split_block(block_t *block, size_t asize) {

    size_t block_size = get_size(block);

    if ((block_size - asize) >= min_block_size) {
        block_t *block_next;
        write_block(block, asize, true, get_prev_alloc(block),
                    get_prev_mini(block));

        block_next = find_next(block);
        write_block(block_next, block_size - asize, false, true,
                    is_miniblock(block));

        insert_free_block(block_next);
    }
}

block_t *find_fit(size_t asize) {

    // Find fit for miniblocks (first fit)
    if (asize <= min_block_size) {
        if (miniblock_pointer != NULL) {
            return (block_t *)miniblock_pointer;
        }
    }

    // Find size class
    short i = find_size_class(asize);
    while (i < NUM_CLASSES) {
        block_t *start = seglists[i];
        block_t *block = start;

        // BEST (BETTER) FIT
        size_t min_size = (size_t)(-1L);
        block_t *min_block = NULL;
        size_t counter = 0;

        while (block != NULL) {
            size_t block_size = get_size(block);

            if (block_size >= asize && block_size < min_size) {
                min_size = block_size;
                min_block = block;
            }
            counter++;
            if (counter == search_depth) {
                if (min_block != NULL) {
                    return min_block;
                } else {
                    // If not found, restart search on current branch
                    counter = 0;
                }
            }

            block = find_next_free(block);
            if (block == start) { // End of free list
                if (min_block != NULL) {
                    return min_block;
                }
                break;
            }
        }
        i++;
    }

    return NULL;
}
