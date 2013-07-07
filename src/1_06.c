#include <assert.h>
#include <stdio.h>

int main() {
  int value = getchar() != EOF;
  assert(value == 1 || value == 0);
}
