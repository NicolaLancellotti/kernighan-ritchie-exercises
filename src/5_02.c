#include "getch.h"
#include <ctype.h>
#include <stdio.h>

int getfloat(float *pn) {
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
  if (c == '.') {
    float pow;
    c = getch();
    for (pow = 1; isdigit(c); c = getch()) {
      *pn = 10 * *pn + (c - '0');
      pow *= 10.0;
    }
    *pn /= pow;
  }
  *pn *= sign;
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}

int main() {
  float x;
  printf("Value: ");
  if (getfloat(&x) > 0) {
    printf("Float: %f", x);
  }
}
