#include "get_line.h"
#include <printf.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

void print_lines(char const *const line_ptr[], int n) {
  for (int i = 0; i < n; ++i) {
    printf("%s", line_ptr[i]);
  }
}

int main(int argc, char const *argv[]) {
  int lines = 3;

  if (argc == 2) {
    if (argv[1][0] != '-') {
      return 1;
    }
    lines = atoi(&argv[1][1]);
  }
  if (lines <= 0 || argc > 2) {
    return 1;
  }

  char *line_ptr[lines];
  int lengths[lines];

  char line[MAX_LEN];
  int length;

  for (int i = 0; i < lines; ++i) {
    if ((length = get_line(line, MAX_LEN)) > 0) {
      line_ptr[i] = malloc(sizeof(char) * (length + 1));
      lengths[i] = length;
      strcpy(line_ptr[i], line);
    } else {
      print_lines((char const *const *)line_ptr, i);
    }
  }

  while ((length = get_line(line, MAX_LEN)) > 0) {
    char *p = NULL;
    int l;
    if (lengths[0] >= length) {
      p = line_ptr[0];
      l = lengths[0];
    } else {
      free(line_ptr[0]);
      p = malloc(sizeof(char) * (length + 1));
      l = length;
    }
    strcpy(p, line);

    for (int i = 0; i < lines - 1; ++i) {
      line_ptr[i] = line_ptr[i + 1];
      lengths[i] = lengths[i + 1];
    }

    line_ptr[lines - 1] = p;
    lengths[lines - 1] = l;
  }
  print_lines((char const *const *)line_ptr, lines);
}
