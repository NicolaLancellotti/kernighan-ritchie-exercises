#include <assert.h>
#include <string.h>

int strindex(char const s[], char const t[]) {
  for (int i = strlen(s) - strlen(t); i >= 0; --i) {
    int k = 0;
    for (int j = i; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {
    }
    if (t[k] == '\0') {
      return i;
    }
  }
  return -1;
}

int main() {
  assert(strindex("abc1abc", "") == 7);
  assert(strindex("abc1abc", "abc") == 4);
  assert(strindex("abc1abc", "abcd") == -1);
  assert(strindex("abc1abc", "aabc1abc") == -1);
}
