
#include "mm-frontend.h"

static __thread struct thread_metadata_region * _thread_metadata = NULL;

static const int _mmf_objects_per_sb = 128;
static const int _mmf_max_sb_per_class = 32;
static const int _mmf_small_threshold = 8192;
static const int _mmf_small_size_classes[] = {
  16, 32, 48, 64, 72, 128, 256, 512,
  1024, 2048, 4096, 8192
}; /* up to 2 pages is considered "small" */
static const int _mmf_num_size_classes = 
  sizeof(_mmf_small_size_classes) / sizeof(int);

/**
 * Node in a circular unrolled doubly-linked list.
 * Each superblock can hold up to 128 objects of
 * a given size class. The size of the payload block
 * is (128 * size_class).
*/
struct superblock_descriptor {
  void      *payload;
  uint32_t  size_class; // constant
  uint8_t   sb_prev_index;
  uint8_t   sb_next_index;
  uint8_t   sb_curr_index;
  uint8_t   unused;
  uint8_t   obj_list[_mmf_objects_per_sb];
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
 * sb_active: A pointer to the active superblock.
 * This may be null.
*/
typedef struct {
  struct superblock_descriptor *sb_start;
  struct superblock_descriptor *sb_active;
} size_class_header; // 16 bytes

struct thread_metadata_region {
  size_class_header headers[_mmf_num_size_classes];
  sb_desc_region descriptors[_mmf_num_size_classes];
}; // around 55kb, more if descriptor count = 64

static size_t sc_index_from_size(size_t normsize) {
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

static struct thread_metadata_region *
_mmf_thread_init_metadata(pid_t tid) {
  size_t metadata_chunk_size = round_up(
    sizeof(struct thread_metadata_region), _MM_PAGESIZE);

  // mmap this directly; we never return block to pageheap
  void 
}

void *malloc(size_t size) {
  return NULL;
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
