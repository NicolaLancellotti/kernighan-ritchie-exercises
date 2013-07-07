#include <assert.h>
#include <stdio.h>
#include <string.h>

int get_line_pointers(char s[], int lim) {
  char *p = s;
  int c;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *p++ = c;
  }
  if (c == '\n') {
    *p++ = c;
  }
  *p = '\0';
  return p - s;
}

void reverse_pointers(char s[]) {
  char *p = s + strlen(s) - 1;
  while (s < p) {
    char c = *s;
    *s++ = *p;
    *p-- = c;
  }
}

int strindex_pointers(char const s[], char const t[]) {
  for (char const *p = s + strlen(s) - strlen(t); p >= s; --p) {
    char const *k = t;
    for (char const *j = p; *k != '\0' && *j == *k; ++j, ++k) {
    }
    if (*k == '\0') {
      return p - s;
    }
  }
  return -1;
}

int main() {
  {
    char s[100];
    printf("length: %d\n", get_line_pointers(s, sizeof s));
  }
  {
    char s[] = "abc";
    reverse_pointers(s);
    assert(strcmp(s, "cba") == 0);
  }
  {
    assert(strindex_pointers("abc1abc", "") == 7);
    assert(strindex_pointers("abc1abc", "abc") == 4);
    assert(strindex_pointers("abc1abc", "abcd") == -1);
    assert(strindex_pointers("abc1abc", "aabc1abc") == -1);
  }
}
