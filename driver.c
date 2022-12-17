/**
 * @file driver.c
 * @author Makoto Tomokiyo <mtomokiy@andrew.cmu.edu>
 * @brief A driver program to evaluate the allocator
*/

// TODO: make into one include file
#include "src/mm-frontend.h"
#include "src/mm-backend.h"

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
  void **ptrs;
  mm_driver_action *actions;
  int num_actions;
} runtrace_arg;

void parse_trace(char *buf, FILE *trace, mm_driver_action *actions) {
  char c;
  size_t id;
  size_t size;
  char rest[TRACE_READ_LINELEN];
  size_t pos = 0;
  while (fgets(buf, TRACE_READ_LINELEN + 1, trace) != NULL) {
    if (strlen(buf) < 2) {
      return;
    }
    sscanf(buf, "%c %s", &c, rest);
    switch(c) {
      case 'a':
        sscanf(buf, "%c %lu %lu", &c, &id, &size);
        actions[pos].alloc_type = MALLOC;
        actions[pos].block_tag = id;
        actions[pos++].alloc_size = size;
        break;
      case 'f':
        sscanf(buf, "%c %lu", &c, &id);
        actions[pos].alloc_type = FREE;
        actions[pos++].block_tag = id;
        break;
      case 'r':
      case 'c':
      default:
        continue;
    }
  }
  return;
}

void *runtrace(void *arg) {
  runtrace_arg *rt_arg = (runtrace_arg *)arg;
  int num_actions = rt_arg->num_actions;
  mm_driver_action *actions = rt_arg->actions;
  void **ptrs = rt_arg->ptrs;
  for (int i = 0; i < num_actions; i++) {
    void *xalloc_return;
    mm_driver_action op = actions[i];
    switch (op.alloc_type) {
      case MALLOC:
      case CALLOC:
      case REALLOC:
        xalloc_return = malloc(op.alloc_size);
        if (xalloc_return == NULL && op.alloc_size != 0) {
          io_msafe_eprintf("driver: malloc failed.\n");
          exit(1);
        }
        ptrs[op.block_tag] = xalloc_return;
        break;
      case FREE:
        free(ptrs[op.block_tag]);
        ptrs[op.block_tag] = NULL;
        break;
      default:
      io_msafe_eprintf("Driver: Invalid operation.\n");
    }
  }
  io_msafe_eprintf("Malloc arena usage: %lu.\n", current_arena_usage());
  return NULL;
}

void cleanup(void) {
  io_msafe_eprintf("Total arena usage: %lu.\n", current_arena_usage());
}

int main (int argc, char **argv) {
  mm_driver_action *actions;
  FILE *trace;
  char trace_read_buf[TRACE_READ_LINELEN];
  int num_allocs, num_actions;
  void **ptrs;

  if (argc < 2) {
    io_msafe_eprintf("Usage: ./driver <trace>\n");
    exit(0);
  }
  atexit(cleanup);
  
  trace = fopen(argv[1], "r");
  io_msafe_assert(trace != NULL);

  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace); // first line
  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace);
  io_msafe_assert(sscanf(trace_read_buf, "%d", &num_allocs) == 1);

  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace);
  io_msafe_assert(sscanf(trace_read_buf, "%d", &num_actions) == 1);
  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace); // heapsize line; ignore

  actions = alloca(num_actions * sizeof(mm_driver_action));
  io_msafe_assert(actions != NULL);

  ptrs = alloca(num_allocs * sizeof(void *));
  io_msafe_assert(ptrs != NULL);

  parse_trace(trace_read_buf, trace, actions);
  fclose(trace);

  pthread_t tid;
  runtrace_arg arg = {.actions = actions, .ptrs = ptrs, .num_actions = num_actions};
  // runtrace((void*)&arg);
  pthread_create(&tid, NULL, runtrace, (void *)&arg);
  pthread_join(tid, NULL);
  return 0;
}
