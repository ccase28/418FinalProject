#ifndef _MM_FRONTEND_H
#define _MM_FRONTEND_H

#include "mm-backend.h"
#include <pthread.h>

extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *calloc(size_t nmemb, size_t size);
extern void *realloc(void *ptr, size_t size);

#endif /*_MM_FRONTEND_H */
