/**
 * @file driver.c
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief A driver program to evaluate the allocator
*/

// TODO: make into one include file
#include "src/mm-frontend.h"
#include "src/mm-backend.h"
#include <getopt.h>

#define TRACE_READ_LINELEN 50

typedef enum {
  MALLOC,
  FREE,
  REALLOC,
  CALLOC
} mm_alloc_type;

typedef struct {
  uint64_t block_tag;
  size_t alloc_size;
  mm_alloc_type alloc_type;
  uint16_t tid;
} mm_driver_action;

typedef struct {
  mm_driver_action **act;
  int nops;
} runtrace_arg;

void **ptrs;

size_t parse_trace(char *buf, FILE *trace, mm_driver_action *actions,
                int *ops_per_thread) {
  char c;
  int tid;
  size_t id, size, nthreads = 0;
  char rest[TRACE_READ_LINELEN];
  size_t pos = 0;
  while (fgets(buf, TRACE_READ_LINELEN + 1, trace) != NULL) {
    if (strlen(buf) < 2) {
      exit(1);
    }
    sscanf(buf, "%d %c %s", &tid, &c, rest);
    nthreads = nthreads > tid ? nthreads : tid;
    ops_per_thread[tid]++;
    switch(c) {
      case 'a':
        sscanf(buf, "%d %c %lu %lu", &tid, &c, &id, &size);
        actions[pos].alloc_type = MALLOC;
        actions[pos].block_tag = id;
        actions[pos].tid = tid;
        actions[pos++].alloc_size = size;
        break;
      case 'f':
        sscanf(buf, "%d %c %lu", &tid, &c, &id);
        actions[pos].alloc_type = FREE;
        actions[pos].tid = tid;
        actions[pos++].block_tag = id;
        break;
      case 'r':
      case 'c':
      default:
        continue;
    }
  }
  return nthreads;
}

void *runtrace(void *argvp) {
  runtrace_arg *arg = (runtrace_arg *)argvp;
  mm_driver_action **actions = arg->act;
  int num_actions = arg->nops;

  for (int i = 0; i < num_actions; i++) {
    void *xalloc_return;
    mm_driver_action *op = actions[i];
    switch (op->alloc_type) {
      case MALLOC:
      case CALLOC:
      case REALLOC:
        xalloc_return = malloc(op->alloc_size);
        if (xalloc_return == NULL && op->alloc_size != 0) {
          io_msafe_eprintf("driver: malloc failed.\n");
          exit(1);
        }
        ptrs[op->block_tag] = xalloc_return;
        break;
      case FREE:
        free(ptrs[op->block_tag]);
        ptrs[op->block_tag] = NULL;
        break;
      default:
      io_msafe_eprintf("Driver: Invalid operation %d.\n", op->alloc_type);
      exit(1);
    }
  }
  return NULL;
}

void cleanup(void) {
  io_msafe_eprintf("Total arena usage: %lu.\n", current_arena_usage(0));
}

int main (int argc, char **argv) {
  mm_driver_action *actions;
  FILE *trace;
  char trace_read_buf[TRACE_READ_LINELEN];
  int ops_per_thread[_MM_INITIAL_NUM_THREADS] = {0};
  int num_allocs, num_actions;

  atexit(cleanup);
  
  if (argc < 2) {
    io_msafe_eprintf("Usage: ./driver <trace>\n");
    exit(0);
  }
  trace = fopen(argv[1], "r");
  io_msafe_assert(trace != NULL);

  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace);
  io_msafe_assert(sscanf(trace_read_buf, "%d", &num_allocs) == 1);

  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace);
  io_msafe_assert(sscanf(trace_read_buf, "%d", &num_actions) == 1);

  actions = malloc(num_actions * sizeof(mm_driver_action));
  io_msafe_assert(actions != NULL);

  ptrs = malloc(num_allocs * sizeof(void *));
  io_msafe_assert(ptrs != NULL);

  size_t maxtid = parse_trace(trace_read_buf, trace, actions, ops_per_thread);
  fclose(trace);
  mm_driver_action **thread_actions[maxtid + 1]; // list of each thread's actions
  int count[maxtid + 1];
  // pthread_t tids[maxtid + 1];
  memset(count, 0, (maxtid + 1) * sizeof(int));
  for (int i = 0; i <= maxtid; i++) {
    thread_actions[i] = malloc(ops_per_thread[i] * sizeof(void *));
  }
  for (int i = 0; i < num_actions; i++) {
    int thread = actions[i].tid;
    int index = count[thread]++;
    thread_actions[thread][index] = actions + i;
  }
  for (int i = 0; i <= maxtid; i++) {
    runtrace_arg *arg = malloc(sizeof(runtrace_arg));
    arg->act = thread_actions[i];
    arg->nops = ops_per_thread[i];
    runtrace((void *)arg);
    // pthread_create(&tids[i], NULL, runtrace, (void *)arg);
  }
  // for (int i = 0; i < maxtid; i++) {
  //   pthread_join(tids[i], NULL);
  // }

  return 0;
}