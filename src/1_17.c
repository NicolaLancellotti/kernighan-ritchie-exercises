#include "get_line.h"
#include <stdio.h>

#define MAXLINE 1000

int main() {
  char line[MAXLINE];
  int len;
  while ((len = get_line(line, MAXLINE)) > 0) {
    if (len > 10) {
      printf("%s", line);
    }
  }
}
