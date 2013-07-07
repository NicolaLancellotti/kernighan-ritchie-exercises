#include "getch.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

int getint(int *pn) {
  int c;
  while (isspace(c = getch())) {
  }

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }

  int sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(c);
      ungetch(sign == 1 ? '+' : '-');
      return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}

int main() {
  int x;
  printf("Value: "); // Insert: +A
  assert(!getint(&x));
  assert(getch() == '+');
  assert(getch() == 'A');
}
