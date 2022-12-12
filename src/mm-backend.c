#include "mm-backend.h"

// modified from csapp memlib.c

/* private global variables */
static struct thread_heap_info *mm_arenas;
static size_t init_mmap_length = TOTAL_ALLOC_SPACE; /* Number of bytes allocated by mmap */
static size_t _mm_sys_pagesize;
static bool meta_init_done = false;
static pthread_mutex_t meta_init_lock = PTHREAD_MUTEX_INITIALIZER;

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
    pthread_mutex_lock(&meta_init_lock);
    _mm_mfence();
    if (meta_init_done) {
        pthread_mutex_unlock(&meta_init_lock);
        return;
    }
    _mm_sys_pagesize = getpagesize();
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
    meta_init_done = true;
    _mm_mfence(); // mfence the done flag
    pthread_mutex_unlock(&meta_init_lock);
    return;
}

/**
 * heap_deinit - free a thread's heap.
 * TODO: register tid as done, to be munmapd when block count goes to 0
 */
void *heap_deinit(void *arg) {
    // int tid = ((tid_as_ptr)arg).argid;
    // munmap(mm_arenas[tid].heap_start, init_mmap_length);
    (void)arg;
    return NULL;
}

/*
 * init_single_heap - initialize the memory system model
 */
struct thread_heap_info *init_single_heap(pid_t tid) {
    struct thread_heap_info *domain_arena;
    if (tid >= _MM_INITIAL_NUM_THREADS) {
        io_msafe_eprintf("FAILURE: thread ID %d out of bounds.\n", tid);
        exit(1);
    }
    if (!meta_init_done) {
        initialize_arena_metadata();
    }
    // tid_as_ptr cleanup_arg = {.argid = tid};
    // pthread_cleanup_push(heap_deinit, cleanup_arg.argp);

    void *start = (void *)((tid + 1) * (size_t)TRY_ALLOC_START);
    int map_try_hugepage = 0; // MAP_HUGETLB;
    int prot = PROT_READ | PROT_WRITE;
init_single_try_mmap:
    void *addr = mmap(start,                       /* suggested start */
                      init_mmap_length,            /* length */
                      prot,                        /* access control */
                      MAP_PRIVATE | MAP_ANONYMOUS | map_try_hugepage,
                      -1,                          /* fd */
                      0);                          /* offset */
    if (addr == MAP_FAILED) {
        if (map_try_hugepage) {
            map_try_hugepage = 0;
            goto init_single_try_mmap;
        }
        io_msafe_eprintf("FAILURE.  mmap couldn't allocate space for heap (%s)\n",
        strerror(errno));
        exit(1);
    }
    io_msafe_eprintf_dbg(
        "Heap for thread %d initialized at address %p.\n",
        tid, addr);
    /* check system page alignment */
    if (round_address_down(addr, _mm_sys_pagesize) != addr) {
        io_msafe_eprintf(
            "FAILURE. Initial heap address (%p) is not page aligned\n",
            addr);
    }
    domain_arena = &mm_arenas[tid];
    pthread_mutex_init(&domain_arena->lock, NULL);
    domain_arena->heap_start = addr;
    domain_arena->max_addr = addr + init_mmap_length;
    domain_arena->bmp = addr;
    domain_arena->bmp_chunk = addr; // do init_done in caller
    domain_arena->_mm_caller_tid_internal = tid;
    return domain_arena;
}

void reset_bmp_ptr(pid_t tid) {
    mm_arenas[tid].bmp = mm_arenas[tid].heap_start;
    mm_arenas[tid].bmp_chunk = mm_arenas[tid].heap_start;
}

void *extend_bmp(intptr_t incr, pid_t tid) {
    if (!meta_init_done || !mm_arenas[tid].thread_init_done) {
        init_single_heap(tid);
    }
    struct thread_heap_info local_heap = mm_arenas[tid];
    unsigned char *old_bmp = local_heap.bmp;

    if (incr < 0) {
        io_msafe_eprintf(
            "ERROR: extend_bmp failed.  Attempt to expand heap by negative "
            "value %ld\n",
                (long)incr);
        errno = EINVAL;
        return _MM_EXTEND_BMP_FAIL;
    }
    if (local_heap.bmp + incr > local_heap.max_addr) {
        ptrdiff_t alloc = local_heap.bmp - local_heap.heap_start + incr;
        io_msafe_eprintf(
                "ERROR: extend_bmp failed. Ran out of memory.  Would require "
                "heap size of %td (0x%zx) bytes\n",
                alloc, alloc);
        errno = ENOMEM;
        return _MM_EXTEND_BMP_FAIL;
    }

    unsigned char *new_bmp = old_bmp + incr;
    unsigned char *new_bmp_chunk = round_address_up(new_bmp, _mm_sys_pagesize);
    /* Make the requested section of the heap be accessible. */
    if (new_bmp_chunk > local_heap.bmp_chunk &&
        mprotect(local_heap.bmp_chunk, (size_t)(new_bmp_chunk - local_heap.bmp_chunk),
                    PROT_READ | PROT_WRITE) == -1) {
        io_msafe_eprintf(
                "ERROR: making %zd bytes at %p accessible failed (%s)\n",
                new_bmp_chunk - local_heap.bmp_chunk, (void *)local_heap.bmp_chunk,
                strerror(errno));
        _MM_EXTEND_BMP_FAIL;
    }

    mm_arenas[tid].bmp_chunk = new_bmp_chunk;
    mm_arenas[tid].bmp = new_bmp;
    return old_bmp;
}

// TODO: change this function
void *mem_heap_hi(pid_t tid) {
    if (!mm_arenas[tid].thread_init_done) {
        io_msafe_eprintf(
        "mem_heap_hi: heap not initialized for thread %d.\n",
        tid);
    }
    return (void *)(mm_arenas[tid].bmp - 1);
}

struct thread_heap_info *nonlocal_context_from_ptr(void *ptr) {
    for (int i = 0; i < _MM_INITIAL_NUM_THREADS; i++) {
        if (mm_arenas[i].thread_init_done
        && (uintptr_t)mm_arenas[i].heap_start <= (uintptr_t)ptr
        && (uintptr_t)mm_arenas[i].max_addr >= (uintptr_t)ptr) {
            return &mm_arenas[i];
        }
    }
    io_msafe_eprintf("Unable to find address %p in heap.\n", ptr);
    return NULL;
}


size_t current_arena_usage(pid_t tid) {
    if (!mm_arenas[tid].thread_init_done) {
        io_msafe_eprintf(
        "current_arena_usage: heap not initialized for thread %d.\n",
        tid);
    }
    return (size_t)(mm_arenas[tid].bmp - mm_arenas[tid].heap_start);
}
