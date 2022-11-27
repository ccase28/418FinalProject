#ifndef _COMMON_H
#define _COMMON_H

#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>

/* Option to expand heap size */
#ifndef TOTAL_ALLOC_SPACE
#define TOTAL_ALLOC_SPACE (1UL << 30) /* 1 GiB */
#endif
#define TRY_ALLOC_START (void *)0x8000000

#endif // _COMMON_H