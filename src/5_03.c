#include <assert.h>
#include <string.h>

void strcat_1(char *s, char const *t) {
  while (*s) {
    ++s;
  }
  while ((*s++ = *t++)) {
  }
}

int main() {
  char s[5] = "AB";
  char const t[] = "CD";
  strcat_1(s, t);
  assert(!strcmp(s, "ABCD"));
}
