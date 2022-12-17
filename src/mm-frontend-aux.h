#ifndef _MM_FRONTEND_AUX_H
#define _MM_FRONTEND_AUX_H

#include "mm-frontend.h"

#define _MMF_OBJECTS_PER_SB (255)
#define _MMF_MAX_SB_PER_CLASS (32)
#define _MMF_NUM_SIZE_CLASSES (12)
#define _MMF_SMALL_THRESHOLD (8192)

enum _mmf_alloc_type {_MMF_ALLOC, _MMF_FREE};

/**
 * Node in a circular unrolled doubly-linked list.
 * Each superblock can hold up to 128 objects of
 * a given size class. The size of the payload block
 * is (128 * size_class).
*/
struct superblock_descriptor {
  void      *payload;
  struct {
  uint16_t  size_class;     /* Size of blocks the superblock contains */
  uint8_t   num_available;  /* Number of free objects in superblock */
  uint8_t   sb_prev_index;  /* Index of previous active superblock */
  uint8_t   sb_next_index;  /* Index of next active superblock */
  uint8_t   freelist_head;  /* Head index of inner free list */
  uint8_t   unused[2];      /* Padding; could be used later */
  };
  uint8_t   obj_list[_MMF_OBJECTS_PER_SB];  /* Free list */
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
  uint8_t  sb_active;                     /* Index of the active superblock */
  uint8_t  active_sb_count;               /* Number of active superblocks */
  uint8_t  sb_inactive_head;              /* Head of the inactive list */
  uint8_t  sb_inactive_list[_MMF_MAX_SB_PER_CLASS];
} size_class_header; // 16 bytes

struct thread_metadata_region {
  size_class_header headers[_MMF_NUM_SIZE_CLASSES];
  sb_desc_region descriptors[_MMF_MAX_SB_PER_CLASS];
}; // around 55kb, more if descriptor count = 64

struct superblock_descriptor *get_active_sb(size_class_header *h);

struct superblock_descriptor *
get_prev_sb(size_class_header *h, struct superblock_descriptor *sb) 
__attribute__ ((unused));

struct superblock_descriptor *
get_next_sb(size_class_header *h, struct superblock_descriptor *sb);

bool _mmf_cas8(uint8_t *dest, uint8_t swapval, uint8_t cmpval) __attribute__ ((naked));

size_t round_request_size(size_t reqsize);

short sc_index_from_size(size_t normsize);

pid_t _mmf_hash_tid(pid_t sys_tid) __attribute__ ((unused));

pid_t _mmf_thread_init_metadata(void);

void add_new_superblock(size_class_header *header, 
                              void *pages, size_t obj_count);

bool augment_size_class(size_class_header *header);

#endif // _MM_FRONTEND_AUX_H