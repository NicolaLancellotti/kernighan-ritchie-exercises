#include <assert.h>

int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c; }

int main() {
  assert(lower('a') == 'a');
  assert(lower('A') == 'a');
}
