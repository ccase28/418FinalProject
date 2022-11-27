#include <stdio.h>
#include "src/mm-frontend.h"

int main (void) {
  void *p = malloc(5);
  if (p == NULL) {
    printf("malloc returned NULL.\n");
  } else {
    size_t *hdr = (size_t *)p - 1;
    size_t size = *hdr & ~0xFL; 
    printf("malloc returned pointer at address %p with size %lu.\n", p, size);
  }
  return 0;
}