#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = (int)strlen(s) - 1; i < j; ++i, --j) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char s[], int min_width) {
  int negative = n < 0;
  int i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10);
  if (negative) {
    s[i++] = '-';
  }
  while (i < min_width) {
    s[i++] = ' ';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  char s[LENGTH];
  int value = 100;
  itoa(value, s, 4);
  assert(!strcmp(s, " 100"));
}
