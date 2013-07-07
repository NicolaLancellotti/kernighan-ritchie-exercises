#include <stdio.h>

int main(int argc, char const *argv[]) {
  FILE *fp;
  for (int i = 1; i < argc; ++i) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "cannot open %s\n", argv[i]);
    } else {
      printf("File: %s count: %d\n", argv[i], i);
      for (int c; (c = getc(fp)) != EOF;) {
        putchar(c);
      }
      printf("\n\n");
      fclose(fp);
    }
  }
}
