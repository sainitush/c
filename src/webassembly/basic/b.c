#include "_wasm_.h"
#include <stdio.h>

EMSCRIPTEN_KEEPALIVE
int
version() {
  return 0x11223344;
}

EMSCRIPTEN_KEEPALIVE
int
add_10(int x) {
  return x+10;
}
  
EMSCRIPTEN_KEEPALIVE
size_t
fact(size_t n, size_t i, size_t acc) {
  if (i > n) {
    return acc;
  }
  return fact(n, i+1, i*acc);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  printf("Hello, WASM\n");
  printf("fact(%zu) = %zu\n", 10ul, fact(10, 1, 1));
  
  return 0;
}
