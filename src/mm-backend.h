#ifndef _MM_BACKEND_H
#define _MM_BACKEND_H

#include "mm-comm.h"

#define _MM_EXTEND_BMP_FAIL ((void *)-1L)
#define _MM_INITIAL_NUM_THREADS 128
#define _MM_MAX_METADATA_BLOCKSIZE (1 << 14) /* 4 pages */

#define thread_extend_bmp(incr) (extend_bmp(incr, caller_tid))
#define thread_reset_bmp_ptr() (reset_bmp_ptr(caller_tid))
#define thread_current_arena_usage() (current_arena_usage(caller_tid))
#define thread_mem_heap_hi() (mem_heap_hi(caller_tid))

struct thread_heap_info {
  unsigned char *heap_start;  /* Starting address of heap */
  unsigned char *brk;         /* Current position of break */
  unsigned char *brk_chunk;   /* ditto, rounded up to a whole allocation chunk */
  unsigned char *max_addr;    /* Maximum allowable heap address */
  bool thread_init_done;          /* Thread */
};

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
void reset_bmp_ptr(pid_t pid);

/**
 * @brief heap size
*/
size_t current_arena_usage(pid_t pid);

void *mem_heap_hi(pid_t pid);

#endif /* mm-backend.h */