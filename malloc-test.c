#include <stdio.h>
#include "src/mm-frontend.h"
#include "src/mm-frontend-aux.h"

int main (void) {
  uint8_t x = 2;
  uint8_t y = 4;
  uint8_t cmpval = 4;
  if (_mmf_cas8(&y, x, cmpval)) {
    io_msafe_eprintf("cas success: y is %d.\n", y);
  } else {
    io_msafe_eprintf("cas failed.\n");
  }
  void *p = malloc(5);

  for (int i = 0; i < 20; i++) {
    p = malloc(5);
    if (p == NULL) {
      io_msafe_eprintf("MUILL.\n");
    }
  }

  if (p == NULL) {
    printf("malloc returned NULL.\n");
  } else {
    size_t *hdr = (size_t *)p - 1;
    size_t size = *hdr & ~0xFL; 
    printf("malloc returned pointer at address %p with size %lu.\n", p, size);
  }
  return 0;
}