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

void itob(int n, char s[], int b) {
  int negative = n < 0;
  int i = 0;
  do {
    int val = abs(n % b);
    s[i++] = val <= 9 ? val + '0' : val - 10 + 'a';
  } while ((n /= b) != 0);
  if (negative) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  char s[LENGTH];
  int n = 12;

  itob(n, s, 2);
  assert(!strcmp(s, "1100"));

  itob(n, s, 8);
  assert(!strcmp(s, "14"));

  itob(n, s, 16);
  assert(!strcmp(s, "c"));
}
