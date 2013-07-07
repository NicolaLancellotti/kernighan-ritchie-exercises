#include <ctype.h>
#include <stdio.h>

int main() {
  int c;
  int count = 0;
  while ((c = getchar()) != EOF) {
    count++;
    if (count == 20) {
      putchar('\n');
      count = 0;
    }
    if (isgraph(c)) {
      putchar(c);
    } else {
      printf("0X%X", c);
    }
  }
}
