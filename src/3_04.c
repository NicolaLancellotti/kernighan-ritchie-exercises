#include <assert.h>
#include <limits.h>
#include <stdio.h>
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

void itoa1(int n, char s[]) {
  int negative = n < 0;
  unsigned unsigned_n;
  if (negative) {
    if (n == INT_MIN) {
      n++;
      unsigned_n = -n;
      unsigned_n++;
    } else {
      unsigned_n = -n;
    }
  } else {
    unsigned_n = n;
  }
  int i = 0;
  do {
    s[i++] = unsigned_n % 10 + '0';
  } while ((unsigned_n /= 10) > 0);
  if (negative) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

void itoa2(int n, char s[]) {
  int i = 0, sign = n;
  do {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  int value = INT_MIN;
  char result[LENGTH];
  snprintf(result, LENGTH, "%d", value);

  char s[LENGTH];
  itoa1(value, s);
  assert(!strcmp(s, result));
  itoa2(value, s);
  assert(!strcmp(s, result));
}
