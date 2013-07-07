#define Exercise

#ifdef Exercise

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void error(char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

int filecopy(int ifd, int ofd) {
  char buf;
  while (read(ifd, &buf, 1) == 1) {
    if (write(ofd, &buf, 1) != 1) {
      return -1;
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  int fd;
  char const *prog = argv[0];

  if (argc == 1) {
    filecopy(0, 1);
  } else {
    while (--argc > 0) {
      if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
        error("%s: can not open %s\n", prog, *argv);
        exit(1);
      } else {
        if (filecopy(fd, 1) == -1) {
          error("%s: error writing stdout\n", prog);
          exit(2);
        }
        close(fd);
      }
    }
  }
  exit(0);
}

#else

#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE *ifp, FILE *ofp) {
  int c;
  while ((c = getc(ifp)) != EOF) {
    putc(c, ofp);
  }
}

int main(int argc, char const *argv[]) {
  FILE *fp;
  char const *prog = argv[0];

  if (argc == 1) {
    filecopy(stdin, stdout);
  } else {
    while (--argc > 0) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s: can not open %s\n", prog, *argv);
        exit(1);
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      }
    }
  }

  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing stdout\n", prog);
    exit(2);
  }
  exit(0);
}

#endif
