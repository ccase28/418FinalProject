#include "mm-backend.h"

// modified from csapp memlib.c

/* private global variables */
static struct thread_heap_info *mm_arenas;
static size_t init_mmap_length = TOTAL_ALLOC_SPACE; /* Number of bytes allocated by mmap */
static size_t pagesize;
static bool init_done = false;

/**
 * Round an address down to a multiple of a specified power of two.
 * @param addr   The address to be rounded.
 * @param align  The number to round down to a multiple of.
 *               Must be a power of two.
 * @return floor(addr / align) * align (where / is true mathematical division).
 */
static inline void *round_address_down(void *addr, size_t align) {
    io_msafe_assert((align & (align - 1)) == 0);  // true if align is a power of two
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
    io_msafe_assert((align & (align - 1)) == 0);  // true if align is a power of two
    return (void *)(((uintptr_t)addr + align - 1) & ~(align - 1));
}

static void initialize_arena_metadata(void) {
    pagesize = getpagesize();
    size_t metadata_size = _MM_MAX_METADATA_BLOCKSIZE;
    // make sure block can fit metadata
    io_msafe_assert(
        metadata_size >= _MM_INITIAL_NUM_THREADS * sizeof(struct thread_heap_info));
    mm_arenas = mmap(
                NULL,
                metadata_size,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS,
                -1, 
                0);
    if (mm_arenas == MAP_FAILED) {
        io_msafe_eprintf(
            "FAILURE.  mmap couldn't allocate space for metadata (%s)\n",
            strerror(errno));
        exit(1);
    }
    io_msafe_eprintf_dbg(
        "Metadata initialized at address %p.\n", mm_arenas);
    init_done = true;
}

/*
 * heap_init - initialize the memory system model
 */
void heap_init(pid_t tid) {
    if (tid >= _MM_INITIAL_NUM_THREADS) {
        io_msafe_eprintf("FAILURE: thread ID %d out of bounds.\n", tid);
    }
    if (!init_done) {
        initialize_arena_metadata();
    }

    void *start = (void *)((tid + 1) * (size_t)TRY_ALLOC_START);
    int prot = PROT_READ | PROT_WRITE;
    void *addr = mmap(start,                       /* suggested start */
                      init_mmap_length,            /* length */
                      prot,                        /* access control */
                      MAP_PRIVATE | MAP_ANONYMOUS, /* private anonymous mem */
                      -1,                          /* fd */
                      0);                          /* offset */
    if (addr == MAP_FAILED) {
        io_msafe_eprintf("FAILURE.  mmap couldn't allocate space for heap (%s)\n",
        strerror(errno));
        exit(1);
    }
    io_msafe_eprintf_dbg(
        "Heap for thread %d initialized at address %p.\n",
        tid, addr);
    /* check system page alignment */
    if (round_address_down(addr, pagesize) != addr) {
        io_msafe_eprintf(
            "FAILURE. Initial heap address (%p) is not page aligned\n",
            addr);
    }
    mm_arenas[tid].heap_start = addr;
    mm_arenas[tid].max_addr = addr + init_mmap_length;
    mm_arenas[tid].brk = addr;
    mm_arenas[tid].brk_chunk = addr;
    mm_arenas[tid].thread_init_done = true;
}

/*
 * heap_deinit - free the storage used by the memory system model
 */
void heap_deinit(pid_t tid) {
    munmap(mm_arenas[tid].heap_start, init_mmap_length);
}

void reset_bmp_ptr(pid_t tid) {
    mm_arenas[tid].brk = mm_arenas[tid].heap_start;
    mm_arenas[tid].brk_chunk = mm_arenas[tid].heap_start;
}

void *extend_bmp(intptr_t incr, pid_t tid) {
    if (!init_done) {
        heap_init(tid);
    }
    struct thread_heap_info local_heap = mm_arenas[tid];
    unsigned char *old_brk = local_heap.brk;

    if (incr < 0) {
        io_msafe_eprintf(
            "ERROR: mem_sbrk failed.  Attempt to expand heap by negative "
            "value %ld\n",
                (long)incr);
        errno = EINVAL;
        return _MM_EXTEND_BMP_FAIL;
    }
    if (local_heap.brk + incr > local_heap.max_addr) {
        ptrdiff_t alloc = local_heap.brk - local_heap.heap_start + incr;
        io_msafe_eprintf(
                "ERROR: mem_sbrk failed. Ran out of memory.  Would require "
                "heap size of %td (0x%zx) bytes\n",
                alloc, alloc);
        errno = ENOMEM;
        return _MM_EXTEND_BMP_FAIL;
    }

    unsigned char *new_brk = old_brk + incr;
    unsigned char *new_brk_chunk = round_address_up(new_brk, pagesize);
    /* Make the requested section of the heap be accessible.
        * sbrk accepts any 'incr' value, but mprotect only works on
        * full pages.
        */
    if (new_brk_chunk > local_heap.brk_chunk &&
        mprotect(local_heap.brk_chunk, (size_t)(new_brk_chunk - local_heap.brk_chunk),
                    PROT_READ | PROT_WRITE) == -1) {
        io_msafe_eprintf(
                "ERROR: making %zd bytes at %p accessible failed (%s)\n",
                new_brk_chunk - local_heap.brk_chunk, (void *)local_heap.brk_chunk,
                strerror(errno));
        _MM_EXTEND_BMP_FAIL;
    }

    mm_arenas[tid].brk_chunk = new_brk_chunk;
    mm_arenas[tid].brk = new_brk;
    return old_brk;
}

// TODO: change this function
void *mem_heap_hi(pid_t tid) {
    if (!mm_arenas[tid].thread_init_done) {
        io_msafe_eprintf(
        "mem_heap_hi: heap not initialized for thread %d.\n",
        tid);
    }
    return (void *)(mm_arenas[tid].brk - 1);
}


size_t current_arena_usage(pid_t tid) {
    if (!mm_arenas[tid].thread_init_done) {
        io_msafe_eprintf(
        "current_arena_usage: heap not initialized for thread %d.\n",
        tid);
    }
    return (size_t)(mm_arenas[tid].brk - mm_arenas[tid].heap_start);
}
