#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  bool upper_to_lower = false;
  if (strstr(argv[0], "upper_to_lower")) {
    upper_to_lower = true;
  } else if (strstr(argv[0], "lower_to_upper")) {
    upper_to_lower = false;
  } else {
    return 1;
  }

  int c;
  while ((c = getchar()) != EOF) {
    putchar(upper_to_lower ? tolower(c) : toupper(c));
  }
}
