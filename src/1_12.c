#include <stdio.h>

int main() {
  for (int c; (c = getchar()) != EOF;) {
    if (c == ' ' || c == '\t') {
      putchar('\n');
    } else {
      putchar(c);
    }
  }
}
