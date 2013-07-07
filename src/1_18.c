#include "get_line.h"
#include <stdio.h>

#define MAXLINE 1000

void remove_trailing_blanks(char s[], int len) {
  int left = 0;
  while (left < len - 1 && (s[left] == ' ' || s[left] == '\t')) {
    left++;
  }

  int right = len - 1;
  int has_end_line = 0;
  if (s[right] == '\n') {
    has_end_line = 1;
    right--;
  }
  while ((right > 0) && (s[right] == ' ' || s[right] == '\t')) {
    right--;
  }

  int i = 0;
  while (left <= right) {
    s[i++] = s[left++];
  }

  if (has_end_line) {
    s[i++] = '\n';
  }
  s[i] = '\0';
}

int main() {
  char line[MAXLINE];
  int len;
  while ((len = get_line(line, MAXLINE)) > 0) {
    remove_trailing_blanks(line, len);
    if (line[0] != '\n') {
      printf("%s", line);
    }
  }
}
