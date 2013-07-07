#include <assert.h>

#define swap(type, x, y)                                                       \
  {                                                                            \
    type tmp = y;                                                              \
    y = x;                                                                     \
    x = tmp;                                                                   \
  }

int main() {
  float x = 0;
  float y = 1;
  swap(float, x, y);
  assert(x == 1 && y == 0);
}
