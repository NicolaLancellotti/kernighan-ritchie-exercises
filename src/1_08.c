#include <stdio.h>

int main() {
  int nb = 0, nt = 0, nl = 0;
  for (int c = getchar(); c != EOF; c = getchar()) {
    if (c == ' ') {
      ++nb;
    } else if (c == '\t') {
      ++nt;
    } else if (c == '\n') {
      ++nl;
    }
  }
  printf("nb = %d nt = %d nl = %d\n", nb, nt, nl);
}
