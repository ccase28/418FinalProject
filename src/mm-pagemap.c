/**
 * @file mm-pagemap.c
 * @brief The pagemap that keeps track of page spans used by
 * caching threads in the allocator.
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * 
 * Divides the lower 48 bits of addresses in the pageheap into 
 * 4 runs of 12 bits. Lower 12 bits (page offset) are discarded.
 * Each set of 12 bits is used to index into an entry in a three-level
 * radix tree that terminates with the size class index of the 
 * provided pointer.
*/

#include "mm-pagemap.h"
#include "pthread.h"

const int pm_block_size = PM_BLOCK_INDICES * sizeof(void *);
static pagemap_block_t *pagemap_root = NULL;

static inline void decompose_ptr(void *ptr, size_t *indices) {
  uintptr_t raw = (uintptr_t)ptr;
  const size_t mask = (~1UL) >> (64 - PM_INDEX_WIDTH);
  for (int i = 0; i < PM_LEVELS; i++) {
    raw >>= 12;
    indices[i] = raw & mask;
  }
}

static void *test_and_set_ptr(void **loc) {
  void *newblock;
  if (*loc != NULL) return *loc;
  newblock = mmap(NULL, pm_block_size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (!_mmf_cas64((uint64_t *)loc, (uint64_t)newblock, 0UL)) {
      munmap(newblock, pm_block_size); // free if CAS fails
  }
  return *loc;
}

size_class_header *pagemap_lookup(void *ptr) {
  size_t indices[3];
  pagemap_block_t **current = &pagemap_root;
  decompose_ptr(ptr, indices);
  for (int i = 0; i < PM_LEVELS; i++) {
    pagemap_block_t *next_level = test_and_set_ptr(current);
    current = &next_level[indices[i]];
  }
  return (size_class_header *)(*current);
}

void pagemap_reallocate(void *ptr, size_class_header *owner) {
  size_t indices[3];
  pagemap_block_t **current = &pagemap_root;
  decompose_ptr(ptr, indices);
  for (int i = 0; i < PM_LEVELS; i++) {
    pagemap_block_t *next_level = test_and_set_ptr(current);
    current = &next_level[indices[i]];
  }
  *current = (pagemap_block_t *)owner;
}