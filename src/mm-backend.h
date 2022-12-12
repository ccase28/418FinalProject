#ifndef _MM_BACKEND_H
#define _MM_BACKEND_H

#include "mm-comm.h"
#include <dlfcn.h>
#include <pthread.h>

#define _MM_EXTEND_BMP_FAIL ((void *)-1L)
#define _MM_INITIAL_NUM_THREADS 256
#define _MM_MAX_METADATA_BLOCKSIZE (1 << 15) /* 8 pages */
#define NUM_CLASSES 9

#define thread_init_single_heap() \
        (init_single_heap(thread_arena_context->_mm_caller_tid_internal))
#define thread_extend_bmp(incr) \
        (extend_bmp(incr, thread_arena_context->_mm_caller_tid_internal))
#define thread_reset_bmp_ptr() \
        (reset_bmp_ptr(thread_arena_context->_mm_caller_tid_internal))
#define thread_current_arena_usage() \
        (current_arena_usage(thread_arena_context->_mm_caller_tid_internal))
#define thread_mem_heap_hi() \
        (mem_heap_hi(thread_arena_context->_mm_caller_tid_internal))

typedef struct block block_t;
typedef struct miniblock miniblock_t;

struct thread_heap_info {
  pthread_mutex_t lock;          /* Lock on the arena */
  unsigned char *heap_start;     /* Starting address of heap */
  unsigned char *bmp;            /* Current position of bump pointer */
  unsigned char *bmp_chunk;      /* ditto, rounded up to a whole allocation chunk */
  unsigned char *max_addr;       /* Maximum allowable heap address */
  block_t *seglists[NUM_CLASSES];/* Segregated list of free blocks */
  miniblock_t *miniblock_pointer;/* Pointer to miniblock free list */
  pid_t _mm_caller_tid_internal; /* Internal descriptor of calling thread */
  bool thread_init_done;         /* Whether heap is ready for use */
};

struct thread_heap_info *init_single_heap(pid_t tid);

/**
 * @brief Increases usable heap area by incr bytes.
 *
 * @param[in] incr The amount of bytes by which to extend the heap
 * @return The start address of the new heap area (i.e. the previous
 *         breakpoint)
 * @pre `incr > 0`
 */
void *extend_bmp(intptr_t incr, pid_t tid);

/**
 * @brief Resets the heap's bump pointer
 */
void reset_bmp_ptr(pid_t tid);

/**
 * @brief heap size
*/
size_t current_arena_usage(pid_t tid);

void *mem_heap_hi(pid_t tid);

pthread_mutex_t *find_remote_lock(void *ptr);

#endif /* mm-backend.h */