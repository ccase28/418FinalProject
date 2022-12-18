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

const int pm_block_size = sizeof(pagemap_block_t);
static pagemap_block_t *pagemap_root = NULL;

static inline void decompose_ptr(void *ptr, size_t *indices) {
  uintptr_t raw = (uintptr_t)ptr;
  const size_t mask = (~1UL) >> (64 - PM_INDEX_WIDTH);
  for (int i = 0; i < PM_LEVELS; i++) {
    raw >>= 12;
    indices[i] = raw & mask;
  }
}

static void *test_and_set_ptr(void **loc, size_t size) {
  void *newblock;
  if (*loc != NULL) return *loc;
  newblock = mmap(NULL, size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (!_mmf_cas64((uint64_t *)loc, (uint64_t)newblock, 0UL)) {
      munmap(newblock, size); // free if CAS fails
  }
  return *loc;
}

struct superblock_descriptor *pagemap_lookup(void *ptr) {
  size_t indices[3];
  pagemap_block_t *current2, *current = pagemap_root;
  struct superblock_descriptor *owner;
  decompose_ptr(ptr, indices);
  for (int i = 0; i < PM_LEVELS; i++) {
    if (current == NULL)
      return NULL;
    if (i == PM_LEVELS - 1) {
      current = current->next_nonterminal[2 * indices[i]];
      current2 = current->next_nonterminal[2 * indices[i] + 1];
    } else {
    current = current->next_nonterminal[indices[i]];
    }
  }
  owner = (struct superblock_descriptor *)current;
  if ((uintptr_t)owner->payload > (uintptr_t)ptr) {
    io_msafe_eprintf("Returning secondary owner.\n");
    owner = (struct superblock_descriptor *)current2;
    // ptr should be within scope of other owner
    io_msafe_assert((uintptr_t)owner->payload <= (uintptr_t)ptr);
  }
  return owner;
}

void pagemap_reallocate(void *ptr, struct superblock_descriptor *owner) {
  size_t indices[3];
  pagemap_block_t **current = &pagemap_root;
  decompose_ptr(ptr, indices);
  for (int i = 0; i < PM_LEVELS; i++) {
    if (i == PM_LEVELS - 1) {
      pagemap_block_t *next_level = test_and_set_ptr(
                                    (void **)current, pm_block_size * 2);
      current = &next_level->next_nonterminal[2 * indices[i]];
    } else {
      pagemap_block_t *next_level = test_and_set_ptr(
                                    (void **)current, pm_block_size);
      current = &next_level->next_nonterminal[indices[i]];
    }
  }
  if (*current != NULL) { /* fill second owner slot */
    io_msafe_eprintf("Page represented: switching to secondary slot.\n");
    current++;
    assert(!*current);
  }
  *current = (pagemap_block_t *)owner;
}