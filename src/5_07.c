#include "get_line.h"
#include <stdio.h>

#define MAX_LEN 1000
#define MAX_LINES 5000

int read_lines(char lines[MAX_LINES][MAX_LEN]) {
  int line_count = 0;
  int length;
  while (line_count < MAX_LINES &&
         (length = get_line(lines[line_count], MAX_LEN)) > 0) {
    lines[line_count][length - 1] = '\0';
    line_count++;
  }
  return line_count;
}

int main() {
  char lines[MAX_LINES][MAX_LEN];
  int line_count = read_lines(lines);
  for (int i = 0; i < line_count; ++i) {
    printf("%s\n", lines[i]);
  }
}
