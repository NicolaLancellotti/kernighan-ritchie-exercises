#include <assert.h>
#include <string.h>

void strncpy_1(char *dest, char const *src, size_t count) {
  while (*src && count) {
    *dest++ = *src++;
    count--;
  }
  *dest = '\0';
}

void strncat_1(char *dest, char const *src, size_t count) {
  while (*dest) {
    dest++;
  }
  strncpy_1(dest, src, count);
}

long strncmp_1(char const *lhs, char const *rhs, size_t count) {
  for (; count && *lhs == *rhs; ++lhs, ++rhs, --count) {
    if (*lhs == '\0') {
      return 0;
    }
  }
  if (count == 0) {
    return 0;
  }
  return *lhs - *rhs;
}

int main() {
  {
    char s[3];
    strncpy_1(s, "DEF", 2);
    assert(!strcmp(s, "DE"));
  }
  {
    char s[] = "AB";
    strncat_1(s, "CDE", 2);
    assert(!strcmp(s, "ABCD"));
  }
  {
    assert(!strncmp_1("AB1", "AB2", 2));
    assert(strncmp_1("AB1", "AB2", 3) == -1);
  }
}
