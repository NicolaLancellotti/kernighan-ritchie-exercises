#include <assert.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
  unsigned shift = (p + 1 - n);
  unsigned n_ones = ~(~0 << n);
  return (x & ~(n_ones << shift)) | ((y & n_ones) << shift);
}

int main() {
  assert(setbits(0, 3, 3, 5) == 10); // ...0|000|0 -> ...0|101|0
}
