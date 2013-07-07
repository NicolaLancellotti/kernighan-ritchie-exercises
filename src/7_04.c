#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void minscanf(char const *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  for (char const *p = fmt; *p; ++p) {
    if (isspace(*p)) {
      char c = getchar();
      while (isspace(c)) {
        c = getchar();
      }
      ungetc(c, stdin);
      continue;
    }

    if (*p == '%') {
      switch (*++p) {
      case 'd': {
        scanf("%d", va_arg(ap, int *));
        break;
      }
      case 'f': {
        scanf("%f", va_arg(ap, float *));
        break;
      }
      case 's': {
        scanf("%s", va_arg(ap, char *));
        break;
      }
      default:
        exit(1);
      }
    } else if (*p == getchar()) {
      continue;
    } else {
      exit(1);
    }
  }
  va_end(ap);
}

int main() {
  int ival;
  float fval;
  char sval[20];
  minscanf("%d - %f | %s", &ival, &fval, sval);
  printf("%d %f %s", ival, fval, sval);
}
