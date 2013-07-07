#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void find(FILE *file, char const *file_name, char const *pattern, int except,
          int number, int *found) {
  char line[MAXLINE];
  long line_number = 0;
  while (fgets(line, MAXLINE, file) > 0) {
    line_number++;
    if ((strstr(line, pattern) != NULL) != except) {
      if (file_name) {
        printf("%s ", file_name);
      }
      if (number) {
        printf("%ld:", line_number);
      }
      printf("%s", line);
      (*found)++;
    }
  }
}

int main(int argc, char const *argv[]) {
  int c, except = 0, number = 0, found = 0;
  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++argv[0])) {
      switch (c) {
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      default:
        printf("find: illegal option %c\n", c);
        argc = 0;
        found = -1;
        break;
      }
    }
  }
  if (argc-- == 0) {
    printf("Usage: find -x -n pattern [filename ...]\n");
    return found;
  }
  char const *pattern = *argv++;

  if (argc == 0) {
    find(stdin, NULL, pattern, except, number, &found);
  } else {
    while (argc--) {
      char const *file_name = *argv++;
      FILE *file = fopen(file_name, "r");
      find(file, file_name, pattern, except, number, &found);
      fclose(file);
    }
  }
  return found;
}
