#include <stdio.h>

#define MAXLINE 1000

int get_line_without_and(char s[], int lim) {
  int i, c;
  for (i = 0; !(i >= lim - 1 || (c = getchar()) == EOF || c == '\n'); ++i) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}

int main() {
  char line[MAXLINE];
  while (get_line_without_and(line, MAXLINE) > 0) {
    printf("%s", line);
  }
}
