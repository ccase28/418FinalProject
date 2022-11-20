#include <stdio.h>
#include "src/mm-frontend.h"

int main (void) {
  void *p = malloc(5);
  if (p == NULL) {
    printf("malloc works.\n");
  }
  return 0;
}