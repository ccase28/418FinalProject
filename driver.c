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

void parse_trace(FILE *trace, mm_driver_action *actions) {
  return;
}

int main (int argc, char **argv) {
  extern char *optarg;
  extern int optind, opterr, optopt;
  char opt;
  mm_driver_action *actions;
  FILE *trace;
  char trace_read_buf[TRACE_READ_LINELEN];
  int num_allocs, num_actions;
  void **ptrs;

  while ((opt = (char)getopt(argc, argv, "t:")) != -1) {
    switch (opt) {
      case 't':
        assert(optarg != NULL);
        trace = fopen(optarg, "r");
        assert(trace != NULL);
    }
  }

  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace);
  assert(sscanf(trace_read_buf, "%d", &num_allocs) == 1);

  fgets(trace_read_buf, TRACE_READ_LINELEN + 1, trace);
  assert(sscanf(trace_read_buf, "%d", &num_actions) == 1);

  actions = alloca(num_actions * sizeof(mm_driver_action));
  assert(actions != NULL);

  ptrs = alloca(num_allocs * sizeof(void *));
  assert(ptrs != NULL);

  parse_trace(trace, actions);

  for (int i = 0; i < num_actions; i++) {
    void *xalloc_return;
    const char *op_error_msg;
    mm_driver_action op = actions[i];
    switch (op.alloc_type) {
      case MALLOC:
      case CALLOC:
      case REALLOC:
        xalloc_return = malloc(op.alloc_size);
        if (xalloc_return == NULL & op.alloc_size != 0) {
          op_error_msg = "malloc failed.\n";
          write(STDERR_FILENO, op_error_msg, strlen(op_error_msg));
          exit(1);
        }
        ptrs[op.block_tag] = xalloc_return;
        break;
      case FREE:
        ptrs[op.block_tag] = NULL;
    }
  }
  return 0;
}