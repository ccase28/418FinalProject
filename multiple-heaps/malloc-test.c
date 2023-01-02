#include <stdio.h>
#include "src/mm-frontend.h"

int main (void) {
  void *p = malloc(5);
  // size_t i = 5;
  // size_t *ip = (void *)1;
  // _mmf_cas_lock_finalize((void **)&ip, (void *)&i);
  // if (ip == (void *)1) {
  //   printf("cas failed.\n");
  // } else {
  //   printf("new value: %lu. i was %lu.\n", *ip, i);
  // }


  if (p == NULL) {
    io_msafe_eprintf("malloc returned NULL.\n");
  } else {
    size_t *hdr = (size_t *)p - 1;
    size_t size = *hdr & ~0xFL; 
    io_msafe_eprintf("malloc returned pointer at address %p with size %lu.\n", p, size);
  }
  return 0;
}