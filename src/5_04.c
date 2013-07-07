#include <assert.h>
#include <string.h>

int strend(char const *s, char const *t) {
  long ls = strlen(s);
  long lt = strlen(t);
  if (lt > ls) {
    return 0;
  }
  s += ls - lt;
  return strcmp(s, t) ? 0 : 1;
}

int main() {
  char const s[] = "ABCDEF";
  assert(strend(s, "DEF") == 1);
  assert(strend(s, "AEF") == 0);
}
