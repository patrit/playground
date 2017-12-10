#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  printf("WebAssembly loaded\n");
}

int EMSCRIPTEN_KEEPALIVE crand() {
  srand(time(NULL));
  return rand() % 100 + 1;
}

int fib(int n) {
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return (fib(n - 1) + fib(n - 2));
}
