#ifndef _MM_CACHE_DEFNS_H
#define _MM_CACHE_DEFNS_H

#define _MMF_OBJECTS_PER_SB (255) /* strictly less than UINT8_MAX */
#define _MMF_MAX_SB_PER_CLASS (255) /* strictly less than UINT8_MAX */
#define _MMF_NUM_SIZE_CLASSES (12) /* strictly less than UINT8_MAX */
#define _MMF_SMALL_THRESHOLD (8192) /* multiple of _MM_PAGESIZE */

#include "mm-comm.h"

enum _mmf_alloc_type {_MMF_ALLOC, _MMF_FREE};

/**
 * Node in a circular unrolled doubly-linked list.
 * Each superblock can hold up to 128 objects of
 * a given size class. The size of the payload block
 * is (128 * size_class).
*/
struct superblock_descriptor {
  void      *payload;
  struct {  /* 64 bits for atomic compare-and-swap */
  uint16_t  size_class;     /* Size of blocks the superblock contains */
  uint16_t   sb_prev_index;  /* Index of previous active superblock */
  uint16_t   sb_next_index;  /* Index of next active superblock */
  uint16_t   num_available;  /* Number of free objects in superblock */
  uint16_t   freelist_head;  /* Head index of inner free list */
  // uint8_t   unused[2];      /* Padding; could be used later */
  };
  uint16_t   obj_list[_MMF_OBJECTS_PER_SB];  /* Free list */
}; // 144 bytes

typedef 
  struct superblock_descriptor 
  sb_desc_region[_MMF_MAX_SB_PER_CLASS];

/**
 * A header that contains information about the 
 * cached data for a specific size class.
 * 
 * sb_start: the start of the array containing all
 * superblock descriptors for the size class.
 * 
 * sb_active: The index of the active superblock. May be null.
*/
typedef struct {
  struct superblock_descriptor *sb_start; /* Start of the superblock list */
  uint32_t size_class;                    /* Size class of the superblock */
  uint16_t  sb_active;                     /* Index of the active superblock */
  uint16_t  active_sb_count;               /* Number of active superblocks */
  uint16_t  sb_inactive_head;              /* Head of the inactive list */
  uint16_t  sb_inactive_list[_MMF_MAX_SB_PER_CLASS];
} size_class_header; // 16 bytes

struct thread_metadata_region {
  size_class_header headers[_MMF_NUM_SIZE_CLASSES];
  sb_desc_region descriptors[_MMF_NUM_SIZE_CLASSES];
}; // around 55kb, more if descriptor count = 64

#endif // _MM_CACHE_DEFNS_H