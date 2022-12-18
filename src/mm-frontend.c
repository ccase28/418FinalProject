/**
 * @file mm-frontend.h
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief Client-facing malloc, calloc, realloc, free functions
 * with per-thread caches that serve allocations under 2 pages in size.
*/

#include "mm-frontend.h"
#include "mm-frontend-aux.h"
#include "mm-pagemap.h"

size_t bigcount = 0;
extern __thread struct thread_metadata_region * _thread_metadata;

static void *malloc_active(size_class_header *header) {
  uint16_t curr_available, curr_index = header->sb_active;
  struct superblock_descriptor *active = get_active_sb(header);

  typedef uint8_t search_obj_t[header->size_class];
  
  if (!active) {
    return NULL; // empty list
  }

  /* reserve a slot */
  do {
test_new_superblock:
    curr_available = active->num_available;
    // io_msafe_eprintf("avail for class %u = %u.\n", header->size_class, curr_available);
    if (curr_available == 0) {
      /* if current superblock full, go to next */
      curr_index = active->sb_next_index;
      active = &header->sb_start[curr_index];

      /* traversed the whole list, nothing found */
      if (curr_index == header->sb_active) {
        return NULL;
      } else {
        goto test_new_superblock;
      }
    }
  /* if current avail count is unchanged, decrement and push update */
  } while (!_mmf_cas8(&active->num_available, curr_available - 1, curr_available));
  /* slot reserved; use current as active */
  header->sb_active = curr_index;

  /* try to pop block from free list */
  uint8_t *block_list = active->obj_list;
  uint8_t cur_head_idx, next_head_idx;
  do {
    cur_head_idx = active->freelist_head;
    next_head_idx = block_list[cur_head_idx];
    /* if payload head is still cur_head_idx, swap it with next_head_idx */
  } while (!_mmf_cas8(&active->freelist_head, next_head_idx, cur_head_idx));
  return &((search_obj_t *)active->payload)[cur_head_idx];
}

void *malloc(size_t size) {
  size_t objsize;
  short sc_index;
  size_class_header *req_size_class;
  void *payload = NULL;
  
  if (size == 0) return NULL;
  // io_msafe_eprintf("malloc (%lu)\n", size);
  /* Initialize thread metadata */
  if (_thread_metadata == NULL &&
  _mmf_thread_init_metadata() < 0) {
    perror("malloc");
    exit(1);
  }

  // objsize is a power of 2, and thus a multiple of pagesize
  // if greater than min threshold.
  objsize = round_request_size(size);
  if (objsize == 4096) { // TODO: temporary
    bigcount++;
  }
  sc_index = sc_index_from_size(objsize);
  if (sc_index < 0) {
    // malloc from page heap
    return _mm_midend_request_bytes(objsize);
  }
  req_size_class = &_thread_metadata->headers[sc_index];
  
  payload = malloc_active(req_size_class);
  if (!payload) {
    augment_size_class(req_size_class);
    payload = malloc_active(req_size_class);
  }
  return payload;
}

void free(void *ptr) {
  if (ptr == NULL) return; // C standard
  struct superblock_descriptor *desc = pagemap_lookup(ptr);
  if (NULL == desc) { /* too large for cache */
    // io_msafe_eprintf(
    //   "Size class not found for pointer %p.\n", ptr); 
    return;
  }
  /* make sure pointer within bounds */
  size_t payload_idx = ((uintptr_t)ptr - (uintptr_t)desc->payload) / desc->size_class;
  io_msafe_assert(payload_idx <= _MMF_OBJECTS_PER_SB);

  /* push free block onto stack */
  uint8_t *block_list = desc->obj_list;
  uint8_t cur_head_idx, new_head_idx = (uint8_t)payload_idx;
  do {
    cur_head_idx = desc->freelist_head;
    block_list[new_head_idx] = cur_head_idx; // new->next = cur_head
    /* if payload head is still cur_head_idx, swap it with new object */
  } while (!_mmf_cas8(&desc->freelist_head, new_head_idx, cur_head_idx));

  /* broadcast new availability */
  uint8_t avail_now;
  do {
    avail_now = desc->num_available;
  } while (!_mmf_cas8(&desc->num_available, avail_now + 1, avail_now));
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
    io_msafe_eprintf("FATAL: REALLOC.\n");
    exit(1);
    // size_class_header *header;
    size_t copysize;
    void *newptr;

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (NULL == ptr) {
        return malloc(size);
    }

    if (NULL == (newptr = malloc(size))) {
      return NULL;
    }

    /* gets size class of old block and copy */
    copysize = 0; // TODO: implement
    if (size < copysize) {
        copysize = size;
    }
    memcpy(newptr, ptr, copysize);
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
