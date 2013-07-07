#include <assert.h>

int isupper_space(int ch) { return ch >= 'A' && ch <= 'Z'; }

#define isupper_time(ch) ((ch) >= 'A' && (ch) <= 'Z')

int main() {
  assert(isupper_space('A'));
  assert(!isupper_space('a'));
  assert(isupper_time('A'));
  assert(!isupper_time('a'));
}
