#ifndef _MM_MIDEND_H
#define _MM_MIDEND_H

#include "mm-backend.h"
#include "mm-midend-aux.h"
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>

void *_mm_midend_request(size_t num_pages);
void _mm_midend_return(void *ptr);

#endif /*_MM_MIDEND_H */
