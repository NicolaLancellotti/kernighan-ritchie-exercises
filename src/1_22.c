#include "get_line.h"
#include <ctype.h>
#include <stdio.h>

#define N 4
#define LENGTH 100

int main() {
  char line[LENGTH];
  while (get_line(line, LENGTH) > 0) {
    int start = 0;
    int current = 0;
    int last_blank = -1;
    int n = 0;

    while (1) {
      if (line[current] == '\n') {
        printf("%s", &line[start]);
        break;
      }

      if (n != N) {
        if (isblank(line[current])) {
          last_blank = current;
        }
        ++n;
        ++current;
      } else {
        int characters = 1;
        if (last_blank > start) {
          while (last_blank - 1 > start && isblank(line[last_blank - 1])) {
            --last_blank;
          }
          characters = last_blank - start;
        }
        if (characters == 1) {
          characters = N;
        }
        start += printf("%.*s\n", characters, &line[start]) - 1;
        current = start;
        last_blank = -1;
        n = 0;
      }
    }
  }
}
