#ifndef _MM_BACKEND_H
#define _MM_BACKEND_H

#include "mm-comm.h"

/**
 * @brief
 */
void heap_init(void);

/**
 * @brief
 */
void heap_deinit(void);

/**
 * @brief Increases usable heap area by incr bytes.
 *
 * @param[in] incr The amount of bytes by which to extend the heap
 * @return The start address of the new heap area (i.e. the previous
 *         breakpoint)
 * @pre `incr > 0`
 */
void *extend_bmp(intptr_t incr);

/**
 * @brief Resets the heap's bump pointer
 */
void reset_bmp_ptr(void);

/**
 * @brief
*/
size_t current_arena_usage(void);

#endif /* mm-backend.h */