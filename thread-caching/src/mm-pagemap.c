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

// static pthread_mutex_t pageheap_lock = PTHREAD_MUTEX_INITIALIZER;
const int pm_block_size = sizeof(pagemap_block_t);
static pagemap_block_t *pagemap_root = NULL;
// typedef struct {
//   void *p;
//   struct superblock_descriptor *desc;
// } p2desc;
// static p2desc *map = NULL;
// static size_t map_size = 0;
// static size_t map_capacity = 0;

static inline void decompose_ptr(void *ptr, size_t *indices) {
  uintptr_t raw = (uintptr_t)ptr;
  const size_t mask = (~1UL) >> (64 - PM_INDEX_WIDTH);
  for (int i = 0; i < PM_LEVELS; i++) {
    indices[i] = raw & mask;
    raw >>= 12;
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
  // pthread_mutex_lock(&pageheap_lock);
  // size_t idx = find_idx_less_than(ptr);
  // return map[idx].desc;
  // pthread_mutex_unlock(&pageheap_lock);
  size_t indices[4];
  pagemap_block_t *current = pagemap_root;
  struct superblock_descriptor *owner;
  decompose_ptr(ptr, indices);
  for (int i = 0; i < PM_LEVELS; i++) {
    if (current == NULL)
      return NULL;
    current = current->next_nonterminal[indices[i]];
  }
  owner = (struct superblock_descriptor *)current;
  return owner;
}

void pagemap_reallocate(void *ptr, struct superblock_descriptor *owner) {
  // pthread_mutex_lock(&pageheap_lock);
  // if (map == NULL) {
  //   map_capacity = (1 << 25) * sizeof(p2desc);
  //   map = mmap(NULL, map_capacity, PROT_READ | PROT_WRITE,
  //                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  // }
  // if (!map) exit(1);
  // size_t idx = find_idx_less_than(ptr);
  // memmove(&map[idx + 1], &map[idx], map_size - idx);
  // map_size++;
  // map[idx].p = ptr;
  // map[idx].desc = owner;
  // pthread_mutex_unlock(&pageheap_lock);
  size_t indices[4];
  pagemap_block_t **current = &pagemap_root;
  decompose_ptr(ptr, indices);
  for (int i = 0; i < PM_LEVELS; i++) {
    
    pagemap_block_t *next_level = test_and_set_ptr(
                                  (void **)current, pm_block_size);
    current = &next_level->next_nonterminal[indices[i]];
  }
  *current = (pagemap_block_t *)owner;
}