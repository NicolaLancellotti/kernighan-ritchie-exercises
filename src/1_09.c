#include <stdio.h>

int main() {
  int last = -1;
  for (int c; (c = getchar()) != EOF;) {
    if (last != ' ') {
      putchar(c);
    }
    last = c;
  }
}
