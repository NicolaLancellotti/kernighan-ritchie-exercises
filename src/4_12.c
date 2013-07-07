#include <assert.h>
#include <string.h>

#define LENGTH 80

int itoa(int n, char s[], int i) {
  int first = i == 0;
  if (first && n < 0) {
    s[i++] = '-';
    n = -n;
  }

  if (n / 10) {
    i = itoa(n / 10, s, i);
  }

  s[i++] = n % 10 + '0';

  if (first) {
    s[i] = '\0';
  }
  return i;
}

int main() {
  char s[LENGTH];
  itoa(-123, s, 0);
  assert(!strcmp(s, "-123"));
}
