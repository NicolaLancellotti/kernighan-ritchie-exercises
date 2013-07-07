#include <stdio.h>

#define MAXLINE 3

int read_line(char s[], int lim) {
  int i = 0, c;
  while ((c = getchar()) != EOF) {
    if (i < lim - 1) {
      s[i] = c;
    }
    i++;
    if (c == '\n') {
      break;
    }
  }

  if (i < lim - 1) {
    s[i] = '\0';
  } else {
    s[lim - 1] = '\0';
  }
  return i;
}

int main() {
  char line[MAXLINE];
  int len = read_line(line, MAXLINE);
  printf("line: %s\nlength: %d\n", line, len);
}
