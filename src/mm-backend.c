#include "mm-backend.h"

// modified from csapp memlib.c

/* private global variables */
static unsigned char *heap = NULL;           /* Starting address of heap */
static unsigned char *mem_brk = NULL;        /* Current position of break */
static unsigned char *mem_brk_chunk = NULL;  /* ditto, rounded up to a whole allocation chunk */
static unsigned char *mem_max_addr = NULL;   /* Maximum allowable heap address */
static size_t init_mmap_length = TOTAL_ALLOC_SPACE; /* Number of bytes allocated by mmap */
static size_t pagesize;

/**
 * Round an address down to a multiple of a specified power of two.
 * @param addr   The address to be rounded.
 * @param align  The number to round down to a multiple of.
 *               Must be a power of two.
 * @return floor(addr / align) * align (where / is true mathematical division).
 */
static inline void *round_address_down(void *addr, size_t align) {
    assert((align & (align - 1)) == 0);  // true if align is a power of two
    return (void *)((uintptr_t)addr & ~(align - 1));
}

/**
 * Round an address up to a multiple of a specified power of two.
 * @param addr   The address to be rounded.
 * @param align  The number to round up to a multiple of.
 *               Must be a power of two.
 * @return ceil(addr / align) * align (where / is true mathematical division).
 */
static inline void *round_address_up(void *addr, size_t align) {
    assert((align & (align - 1)) == 0);  // true if align is a power of two
    return (void *)(((uintptr_t)addr + align - 1) & ~(align - 1));
}

/*
 * heap_init - initialize the memory system model
 */
void heap_init(void) {

    void *start = TRY_ALLOC_START;
    int prot = PROT_READ | PROT_WRITE;
    void *addr = mmap(start,                       /* suggested start*/
                      init_mmap_length,            /* length */
                      prot,                        /* access control */
                      MAP_PRIVATE | MAP_ANONYMOUS, /* private anonymous mem */
                      -1,                          /* fd */
                      0);                          /* offset */
    if (addr == MAP_FAILED) {
        fprintf(stderr,
                "FAILURE.  mmap couldn't allocate space for heap (%s)\n",
                strerror(errno));
        exit(1);
    }
    /* check system page alignment */
    pagesize = getpagesize();
    if (round_address_down(addr, pagesize) != addr) {
        fprintf(stderr,
                "FAILURE.  Initial heap address (%p) is not page aligned\n",
                addr);
        exit(1);
    }
    heap = addr;
    mem_max_addr = heap + init_mmap_length;
    mem_brk = heap;
    mem_brk_chunk = heap;
}

/*
 * heap_deinit - free the storage used by the memory system model
 */
void heap_deinit(void) {
    munmap(heap, init_mmap_length);
}

void reset_bmp_ptr(void) {
    mem_brk = heap;
    mem_brk_chunk = heap;
}

void *extend_bmp(intptr_t incr) {
    unsigned char *old_brk = mem_brk;

    if (incr < 0) {
        fprintf(stderr,
                "ERROR: mem_sbrk failed.  Attempt to expand heap by negative "
                "value %ld\n",
                (long)incr);
        errno = EINVAL;
        return (void *)-1;
    }
    if (mem_brk + incr > mem_max_addr) {
        ptrdiff_t alloc = mem_brk - heap + incr;
        fprintf(stderr,
                "ERROR: mem_sbrk failed. Ran out of memory.  Would require "
                "heap size of %td (0x%zx) bytes\n",
                alloc, alloc);
        errno = ENOMEM;
        return (void *)-1;
    }

    unsigned char *new_brk = old_brk + incr;
    unsigned char *new_brk_chunk = round_address_up(new_brk, pagesize);
    /* Make the requested section of the heap be accessible.
        * sbrk accepts any 'incr' value, but mprotect only works on
        * full pages.
        */
    if (new_brk_chunk > mem_brk_chunk &&
        mprotect(mem_brk_chunk, (size_t)(new_brk_chunk - mem_brk_chunk),
                    PROT_READ | PROT_WRITE) == -1) {
        fprintf(stderr,
                "ERROR: making %zd bytes at %p accessible failed (%s)\n",
                new_brk_chunk - mem_brk_chunk, (void *)mem_brk_chunk,
                strerror(errno));
        return (void *)-1;
    }

    mem_brk_chunk = new_brk_chunk;
    mem_brk = new_brk;
    return old_brk;
}

size_t current_arena_usage(void) {
    return (size_t)(mem_brk - heap);
}
