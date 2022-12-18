#ifndef _MM_FRONTEND_AUX_H
#define _MM_FRONTEND_AUX_H

#include "mm-cache-defines.h"
#include "mm-frontend.h"

struct superblock_descriptor *get_active_sb(size_class_header *h);

struct superblock_descriptor *
get_prev_sb(size_class_header *h, struct superblock_descriptor *sb) 
__attribute__ ((unused));

struct superblock_descriptor *
get_next_sb(size_class_header *h, struct superblock_descriptor *sb);

bool _mmf_cas64(uint64_t *dest, uint64_t swapval, uint64_t cmpval) __attribute ((naked));

bool _mmf_cas8(uint8_t *dest, uint8_t swapval, uint8_t cmpval) __attribute__ ((naked));

size_t round_request_size(size_t reqsize);

short sc_index_from_size(size_t normsize);

pid_t _mmf_hash_tid(pid_t sys_tid) __attribute__ ((unused));

pid_t _mmf_thread_init_metadata(void);

void add_new_superblock(size_class_header *header, 
                              void *pages, size_t obj_count);

bool augment_size_class(size_class_header *header);

#endif // _MM_FRONTEND_AUX_H