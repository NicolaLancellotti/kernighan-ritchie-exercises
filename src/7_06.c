#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    exit(1);
  }

  FILE *file1 = fopen(argv[1], "r");
  FILE *file2 = fopen(argv[2], "r");
  if (!file1 || !file2) {
    exit(1);
  }

  fpos_t pos1, pos2;
  fgetpos(file1, &pos1);
  fgetpos(file2, &pos2);

  int c;
  while (1) {
    if ((c = getc(file1)) != getc(file2)) {
      break;
    }

    switch (c) {
    case EOF:
      exit(0);
    case '\n':
      fgetpos(file1, &pos1);
      fgetpos(file2, &pos2);
      break;
    }
  }
  fsetpos(file1, &pos1);
  fsetpos(file2, &pos2);

  printf("line: ");
  while ((c = getc(file1)) != EOF && c != '\n') {
    putchar(c);
  }
  if (c == '\n') {
    printf("\\n");
  }

  printf("\nline: ");
  while ((c = getc(file2)) != EOF && c != '\n') {
    putchar(c);
  }
  if (c == '\n') {
    printf("\\n");
  }
}
