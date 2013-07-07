#include <assert.h>

unsigned invert(unsigned x, int p, int n) {
  return x ^ (~(~0 << n) << (p - n + 1));
}

int main() {
  assert(invert(4, 2, 2) == 2); // ...00|10|0 -> ...00|01|0
}
