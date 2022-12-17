/**
 * Make functions visible in debugger.
*/

#include "mm-frontend-aux.h"

/* up to 2 pages is "small" */
static const int _mmf_small_size_classes[] = {
  16, 32, 48, 64, 72, 128, 256, 512,
  1024, 2048, 4096, 8192
};

static size_t _mmf_tid_hash_counter = 0;
__thread struct thread_metadata_region * _thread_metadata = NULL;


/* Get a pointer to the size class' active superblock. */
inline struct superblock_descriptor *get_active_sb(size_class_header *h) {
  return &h->sb_start[h->sb_active];
}

inline struct superblock_descriptor *
get_prev_sb(size_class_header *h,struct superblock_descriptor *sb) {
  return &h->sb_start[sb->sb_prev_index];
}

inline struct superblock_descriptor *get_next_sb(size_class_header *h,
                                            struct superblock_descriptor *sb) {
  return &h->sb_start[sb->sb_next_index];
}

bool _mmf_cas8(uint8_t *dest, uint8_t swapval, uint8_t cmpval) {
  __asm__(
    "movb %dl, %al\n\t"
    "xor %ecx, %ecx\n\t"
    "lock cmpxchg %sil, (%rdi)\n\t"
    "mov $1, %eax\n\t"  // return 1
    "cmovnz %ecx, %eax\n\t" // 0 if compare fails
    "ret\n\t"
  );
}

// TODO: unit test
size_t round_request_size(size_t reqsize) {
  // edge cases
  if (reqsize > 32 && reqsize <= 48) return 48;
  if (reqsize > 64 && reqsize <= 72) return 72;
  reqsize--;
  for (int i = 0; i < 5; i++)
    reqsize |= (reqsize >> (1 << i));
  return max(++reqsize, 16);
}

short sc_index_from_size(size_t normsize) {
  if (normsize > _MMF_SMALL_THRESHOLD) {
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
pid_t _mmf_hash_tid(pid_t sys_tid) {
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
  // _mm_mfence();
  pthread_mutex_unlock(&_mmf_tid_lock);
  return ret;
}

/**
 * @brief Initialize a thread's metadata.
 * @return true if metadata was successfully initialized, 
 * false otherwise
*/
pid_t _mmf_thread_init_metadata(void) {

  // pid_t sys_tid = syscall(__NR_gettid);
  // pid_t internal_tid = _mmf_hash_tid(sys_tid);
  // if (internal_tid < 0) {
  //   return -1; // init failure
  // }

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
      0, strerror(errno));
    exit(1);
  }
  /* Set pointers for all headers;
     head of descriptor list should be null initially. */
  for (int i = 0; i < _MMF_NUM_SIZE_CLASSES; i++) {
    sb_desc_region *sc_descriptors = &region_start->descriptors[i];
    struct superblock_descriptor *desc = sc_descriptors[0];
    size_class_header *header = &region_start->headers[i];
    uint16_t size_limit = _mmf_small_size_classes[i];
    header->sb_start = desc;
    header->active_sb_count = 0;
    header->sb_active = 0; // technically unnecessary
    header->sb_inactive_head = 0;
    for (uint8_t j = 0; j < _MMF_MAX_SB_PER_CLASS; j++) {
      header->sb_inactive_list[j] = j + 1;
    }
    header->size_class = size_limit;
    desc->size_class = size_limit;
  }
  _thread_metadata = region_start;
  return 0;
}

void add_new_superblock(size_class_header *header, 
                              void *pages, size_t obj_count) {
  struct superblock_descriptor *sb;
  uint8_t sb_reclaim_index;

  /* Find a new superblock to use. */
  sb_reclaim_index = header->sb_inactive_head;
  io_msafe_assert(sb_reclaim_index < _MMF_MAX_SB_PER_CLASS);
  io_msafe_assert(header->active_sb_count < _MMF_MAX_SB_PER_CLASS);
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
bool augment_size_class(size_class_header *header) {
  // Request more pages from midend
  void *pages;
  size_t bsize = header->size_class;
  size_t objs_per_sb = _MMF_OBJECTS_PER_SB;
  if (bsize >= 1024) objs_per_sb <<= 2;
  size_t max_sb_size = bsize * objs_per_sb;
  size_t request_bytes = round_up(max_sb_size, _MM_PAGESIZE);

  pages = _mm_midend_request_bytes(request_bytes);
  if (!pages) {
    io_msafe_eprintf(
      "Error requesting %lu bytes from midend.\n",
      request_bytes);
    exit(1);
  }
  io_msafe_eprintf_dbg(
    "Adding superblock of %lu bytes containing "
    "%lu objects of size %lu.\n",
    request_bytes, objs_per_sb, bsize);
  add_new_superblock(header, pages, objs_per_sb);
  return true;
}
