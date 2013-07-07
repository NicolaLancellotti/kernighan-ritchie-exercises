#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

void minprintf(char const *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  char format[10];

  for (char const *p = fmt; *p; ++p) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    p++;
    int i = 0;
    format[i++] = '%';

    if (*p == '-') {
      format[i++] = '-';
      p++;
    }

    while (isnumber(*p)) {
      format[i++] = *p;
      p++;
    }

    if (*p == '.') {
      format[i++] = '.';
      p++;
      while (isnumber(*p)) {
        format[i++] = *p;
        p++;
      }
    }

    switch (*p) {
    case 'd': {
      int ival = va_arg(ap, int);
      format[i++] = 'd';
      format[i] = '\0';
      printf(format, ival);
      break;
    }
    case 'f': {
      double dval = va_arg(ap, double);
      format[i++] = 'f';
      format[i] = '\0';
      printf(format, dval);
      break;
    }
    case 's': {
      char *sval = va_arg(ap, char *);
      format[i++] = 's';
      format[i] = '\0';
      printf(format, sval);
      break;
    }
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap);
}

int main() {
  minprintf("|%10.1d|\n", 1);
  minprintf("|%-10.2d|\n", 1);
  minprintf("|%10.1f|\n", 1.2);
  minprintf("|%-10.2f|\n", 1.2);
  minprintf("|%10s|\n", "abcd");
  minprintf("|%-10.2s|\n", "abcd");
}
