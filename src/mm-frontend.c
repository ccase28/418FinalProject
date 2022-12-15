
#include "mm-frontend.h"

static const int _mmf_objects_per_sb = 128;
static const int _mmf_max_sb_per_class = 32;
static const int _mmf_small_threshold = 8192;
static const int _mmf_small_size_classes[] = {
  16, 32, 48, 64, 72, 128, 256, 512,
  1024, 2048, 4096, 8192
}; /* up to 2 pages is considered "small" */
static const int _mmf_num_size_classes = 
  sizeof(_mmf_small_size_classes) / sizeof(int);

static size_t _mmf_tid_hash_counter = 0;
static __thread struct thread_metadata_region * _thread_metadata = NULL;

static enum _mmf_alloc_type {_MMF_ALLOC, _MMF_FREE};

/**
 * Node in a circular unrolled doubly-linked list.
 * Each superblock can hold up to 128 objects of
 * a given size class. The size of the payload block
 * is (128 * size_class).
*/
static struct superblock_descriptor {
  void      *payload;
  struct {
  uint16_t  size_class;     /* Size of blocks the superblock contains */
  uint8_t   sb_prev_index;  /* Index of previous active superblock */
  uint8_t   sb_next_index;  /* Index of next active superblock */
  uint8_t   num_available;  /* Number of free objects in superblock */
  uint8_t   freelist_head;  /* Head index of inner free list */
  uint8_t   unused[2];      /* Padding; could be used later */
  };
  uint8_t   obj_list[_mmf_objects_per_sb];  /* Free list */
}; // 144 bytes

typedef 
  struct superblock_descriptor 
  sb_desc_region[_mmf_max_sb_per_class];

/**
 * A header that contains information about the 
 * cached data for a specific size class.
 * 
 * sb_start: the start of the array containing all
 * superblock descriptors for the size class.
 * 
 * sb_active: The index of the active superblock.
 * This may be null.
 * TODO: we could make sb_active an index (char) but
 * it gets padded anyway
*/
typedef struct {
  struct superblock_descriptor *sb_start; /* Start of the superblock list */
  uint32_t size_class;                    /* Size class of the superblock */
  uint8_t  sb_active;                     /* Index of the active superblock */
  uint8_t  active_sb_count;               /* Number of active superblocks */
  uint8_t  sb_inactive_head;                 /* Head of the inactive list */
  uint8_t  sb_inactive_list[_mmf_max_sb_per_class];
} size_class_header; // 16 bytes

static struct thread_metadata_region {
  size_class_header headers[_mmf_num_size_classes];
  sb_desc_region descriptors[_mmf_num_size_classes];
}; // around 55kb, more if descriptor count = 64

/* Get a pointer to the size class' active superblock. */
static inline struct superblock_descriptor *get_active_sb(size_class_header *h) {
  return &h->sb_start[h->sb_active];
}

static inline struct superblock_descriptor *get_prev_sb(size_class_header *h,
                                            struct superblock_descriptor *sb) {
  return &h->sb_start[sb->sb_prev_index];
}

static inline struct superblock_descriptor *get_next_sb(size_class_header *h,
                                            struct superblock_descriptor *sb) {
  return &h->sb_start[sb->sb_next_index];
}

static bool _mmf_cas(uint64_t *dest, uint64_t swapval, uint64_t cmpval);

// TODO: unit test
static size_t round_request_size(size_t reqsize) {
  // edge cases
  if (reqsize > 32 && reqsize <= 48) return 48;
  if (reqsize > 64 && reqsize <= 72) return 72;
  reqsize--;
  for (int i = 0; i < 5; i++)
    reqsize |= (reqsize >> (1 << i));
  return ++reqsize;
}

static short sc_index_from_size(size_t normsize) {
  if (normsize > _mmf_small_threshold) {
    return -1;
  }
  switch (normsize) {
    case 16:
      return 0;
    case 32:
      return 1;
    case 48:
      return 2;
    case 64:
      return 3;
    case 72:
      return 4;
    case 128:
      return 5;
    case 256:
      return 6;
    case 512:
      return 7;
    case 1024:
      return 8;
    case 2048:
      return 9;
    case 4096:
      return 10;
    case 8192:
      return 11;
    default:
      io_msafe_eprintf(
        "Error: input size %lu not normalized.\n",
        normsize);
      return 0;
  }
}

/**
 * @brief Temporary function to assign incoming TIDs.
 * TODO: we could also make this CAS-based but it's a once-per-thread operation
 * so probably not a priority
*/
static pid_t _mmf_hash_tid(pid_t sys_tid) {
  (void) sys_tid;
  static pthread_mutex_t _mmf_tid_lock = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&_mmf_tid_lock);
  pid_t ret = _mmf_tid_hash_counter++;
  if (_mmf_tid_hash_counter >= _MM_HARD_THREAD_LIMIT) {
      io_msafe_eprintf(
          "FAILURE: concurrent thread count exceeds max of %d.\n",
          _MM_HARD_THREAD_LIMIT);
      errno = ENOMEM;
      return -1;
  }
  _mm_mfence();
  pthread_mutex_unlock(&_mmf_tid_lock);
  return ret;
}

/**
 * @brief Initialize a thread's metadata.
 * @return true if metadata was successfully initialized, 
 * false otherwise
*/
static pid_t _mmf_thread_init_metadata(void) {

  pid_t sys_tid = syscall(__NR_gettid);
  pid_t internal_tid = _mmf_hash_tid(sys_tid);
  if (internal_tid < 0) {
    return -1; // init failure
  }

  size_t metadata_chunk_size = round_up(
    sizeof(struct thread_metadata_region), _MM_PAGESIZE);

  /* mmap this directly; we never return block to pageheap.
     This also zeroes memory for us. */

  struct thread_metadata_region *region_start = mmap
    (NULL,
    metadata_chunk_size,
    PROT_READ | PROT_WRITE,
    MAP_PRIVATE | MAP_ANONYMOUS,
    -1,
    0);
  if (region_start == MAP_FAILED) {
    io_msafe_eprintf(
      "FAILURE. mmap couldn't allocate space for metadata "
      "on thread %d (%s)\n",
      internal_tid, strerror(errno));
    exit(1);
  }
  /* Set pointers for all headers;
     head of descriptor list should be null initially. */
  for (int i = 0; i < _mmf_num_size_classes; i++) {
    struct superblock_descriptor *desc = &region_start->descriptors[i];
    size_class_header *header = &region_start->headers[i];
    uint16_t size_limit = _mmf_small_size_classes[i];
    header->sb_start = desc;
    header->active_sb_count = 0;
    header->sb_active = 0; // technically unnecessary
    header->sb_inactive_head = 0;
    for (uint8_t j = 0; j < _mmf_max_sb_per_class; j++) {
      header->sb_inactive_list[j] = j + 1;
    }
    header->size_class = size_limit;
    desc->size_class = size_limit;
  }
  _thread_metadata = region_start;
  return internal_tid;
}

static void add_new_superblock(size_class_header *header, 
                              void *pages, size_t obj_count) {
  struct superblock_descriptor *sb;
  uint8_t sb_reclaim_index;

  /* Find a new superblock to use. */
  sb_reclaim_index = header->sb_inactive_head;
  io_msafe_assert(sb_reclaim_index < _mmf_max_sb_per_class);
  io_msafe_assert(header->active_sb_count < _mmf_max_sb_per_class);
  sb = &header->sb_start[sb_reclaim_index];

  /* Write new internal free stack. */
  sb->freelist_head = 0;
  for (int i = 0; i < obj_count - 1; i++) {
    sb->obj_list[i] = i + 1; /* don't write to last index */
  }
  sb->payload = pages;
  sb->num_available = obj_count;

  /* Add initialized superblock to list (after active). */
  if (header->active_sb_count == 0) { /* no active superblocks */
    header->sb_active = sb_reclaim_index;
    sb->sb_prev_index = sb_reclaim_index; // self
    sb->sb_next_index = sb_reclaim_index;
  } else { /* at least 1 active superblock */
    struct superblock_descriptor *cur_active = get_active_sb(header);
    struct superblock_descriptor *nxt_active = get_next_sb(header, cur_active);
    sb->sb_prev_index = header->sb_active;
    sb->sb_next_index = cur_active->sb_next_index;
    nxt_active->sb_prev_index = sb_reclaim_index;
    cur_active->sb_next_index = sb_reclaim_index;
  }

  /* Remove initialized superblock from empty SB list. */
  /* Bump head pointer one forward. It's ok if next is a bogus index if last */
  header->sb_inactive_head = header->sb_inactive_list[header->sb_inactive_head];
  header->active_sb_count++;
}

/**
 * @brief Replenish a size class with superblocks from page heap.
*/
static bool augment_size_class(size_class_header *header) {
  // Request more pages from midend
  void *pages;
  size_t request_pages, request_size, sb_count, objs_per_sb;
  size_t max_sb_storage, rem, bsize = header->size_class;

  /* Everything should be able to fit into one superblock. */
  if (bsize <= 64) {
    request_pages = 2;
    // request_size = 1UL << 13; // 8192
  } else if (bsize <= 1024) {
    request_pages = 4;
    // request_size = 1UL << 14; // 16384
  } else {
    request_pages = 16;
    // request_size = 1UL << 16; // 64k
  }

  // build up linked list
  if (header->active_sb_count == _mmf_max_sb_per_class) {
    io_msafe_eprintf(
      "Unable to allocate more data: superblock limit reached.\n");
    return false;
  }
  pages = _mm_midend_request_pages(request_pages);
  if (NULL == pages) {
    io_msafe_eprintf(
      "Error requesting %lu bytes from midend.\n",
      request_size);
  }
  objs_per_sb = (request_pages * _MM_PAGESIZE) / bsize;
  io_msafe_assert(objs_per_sb <= _mmf_objects_per_sb);
  add_new_superblock(header, pages, objs_per_sb);
  return true;
}

/**
 * @brief Return free superblocks to page heap.
*/
static void cleanup_size_class(size_class_header *header) {
  return;
}

static void *malloc_active(size_class_header *header) {
  uint8_t curr_available;
  struct superblock_descriptor *active = get_active_sb(header);

  typedef uint8_t search_obj_t[header->size_class];
  
  if (!active) {
    return NULL; // empty list
  }

// reserve slot
get_active_block: do {
    curr_available = active->num_available;
    if (curr_available == 0) {
      // switch to next superblock
      // handle case where all superblocks are exhausted
      // (return null)
    }
  // restrict to 8 bits

  } while (!_mmf_cas(&active->num_available, curr_available + 1, curr_available));
  /* slot reserved */
  // pop block from free list
  uint8_t *block_list = active->obj_list;
  uint8_t cur_head_node, cur_head_idx, next_head_idx;
  do {
    cur_head_idx = active->freelist_head;
    cur_head_node = block_list[cur_head_idx];
    next_head_idx = _mmf_get_next_free(cur_head_node);
    /* if payload head is still cur_head_idx, swap it with next_head_idx */
  } while (!_mmf_cas(&active->freelist_head, next_head_idx, cur_head_idx));
  // _mmf_mark_block(block_list, _MMF_ALLOC); // only needed for RA
  io_msafe_assert(cur_head_idx < _mmf_objects_per_sb);
  return &((search_obj_t *)active->payload)[cur_head_idx];
}

void *malloc(size_t size) {
  size_t objsize;
  short sc_index;
  size_class_header *req_size_class;
  void *payload = NULL;
  
  if (size == 0) return NULL;

  /* Initialize thread metadata */
  if (_thread_metadata == NULL &&
  _mmf_thread_init_metadata() < 0) {
    perror("malloc");
    exit(1);
  }

  // objsize is a power of 2, and thus a multiple of pagesize
  // if greater than min threshold.
  objsize = round_request_size(size);
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
  return;
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
