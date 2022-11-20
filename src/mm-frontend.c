/**
 * @author Makoto Tomokiyo (mtomokiy)
 * @file mm.c
 * @brief A 64-bit struct-based segregated free list memory allocator
 *
 *
 *************************************************************************
 * ALLOCATOR DESIGN
 *
 * Free and allocated blocks are stored on the heap, with support for forward
 *and limited backward navigation among consecutive blocks.
 *
 * Allocated blocks have an 8-byte header which is formatted as follows:
 *  - Block size (64 bits)
 *  - Previous block miniblock flag (1 bit)
 *  - Previous block allocation status (1 bit)
 *  - Current block allocation status (1 bit)
 *
 * The payload of an allocated block is represented as zero-length array to
 * allow for dynamic allocation of various payload sizes.
 *
 * Free blocks have identical 8-byte headers and footers that allow for fast
 * coalescing. The 16 bytes between the header and footer, which holds the
 * payload in an allocated block, instead hold a pair of pointers that allow for
 * navigation among an explicit free list.
 *
 * Miniblocks are special blocks used to handle small (at most 8 bytes)
 * payloads, and use the same header structure as full blocks. Similarly, free
 * miniblocks do not have footers. An allocated miniblock consists of the header
 * followed by an 8-byte payload allowance. A free miniblock superposes a
 * miniblock pointer over the payload field, which points to another free
 * miniblock and allows linear list-like navigation between free miniblocks.
 *
 * Free miniblocks are structured as a linear list with constant-time forward
 * navigation and insertion, as well as deletion in linear time.
 *
 * All other free blocks are organized by an array of circular doubly-linked
 * lists that are segregated according to a specified set of size classes. This
 * structure supports constant-time insertion, deletion, and forward/backward
 * navigation among a single size class list.
 *
 * All free blocks are coalesced with both neighbors immediately after being
 * marked as free.
 *
 *************************************************************************
 *
 */

#include "mm-frontend.h"

void *malloc(size_t size) {
  return NULL;
}

void free(void *ptr) {
  return;
}

void *calloc(size_t nmemb, size_t size) {
  return NULL;
}

void *realloc(void *ptr, size_t size) {
  return NULL;
}
