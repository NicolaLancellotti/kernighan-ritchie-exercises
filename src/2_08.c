#include <assert.h>

unsigned rightrot(unsigned x, int n) {
  return (x >> n) | ((~(~0 << n) & x) << ((sizeof(unsigned) << 3) - n));
}

int main() {
  assert(rightrot(3, (sizeof(unsigned) << 3) - 1) == 6); // ...0011 -> ...0110
}
