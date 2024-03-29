#include <assert.h>

int bitcount(unsigned x) {
  int b;
  for (b = 0; x != 0; x >>= 1)
    if (x & 01)
      b++;
  return b;
}

int bitcount2(unsigned x) {
  int b;
  for (b = 0; x != 0; x &= (x - 1)) {
    b++;
  }
  return b;
}

int main() {
  int x = 01101;
  assert(bitcount(x) == 3);
  assert(bitcount2(x) == 3);
}
