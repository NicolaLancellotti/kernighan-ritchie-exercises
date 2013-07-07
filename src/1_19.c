#include "get_line.h"
#include <stdio.h>

#define MAXLINE 1000

void reverse(char s[], int len) {
  int has_end_line = 0;
  if (len >= 1 && s[len - 1] == '\n') {
    has_end_line = 1;
  }
  int left = 0;
  int right = has_end_line ? len - 2 : len - 1;
  while (left < right) {
    int tmp = s[left];
    s[left++] = s[right];
    s[right--] = tmp;
  }
}

int main() {
  char line[MAXLINE];
  int len;
  while ((len = get_line(line, MAXLINE)) > 0) {
    reverse(line, len);
    printf("%s", line);
  }
}
