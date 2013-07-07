#include <assert.h>

int any(char s1[], char const s2[]) {
  for (int i = 0; s1[i]; ++i) {
    for (int j = 0; s2[j]; ++j) {
      if (s1[i] == s2[j]) {
        return i;
      }
    }
  }
  return -1;
}

int main() {
  assert(any("abcdef", "hi") == -1);
  assert(any("abcdef", "hd") == 3);
}
