#include <stdio.h>
#include <stdlib.h>

void read_comment(void) {
  for (int c; (c = getchar()) != EOF;) {
    if (c == '*') {
      if ((c = getchar()) == '/') {
        return;
      } else {
        ungetc(c, stdin);
      }
    }
  }
  exit(1);
}

void read_and_print_char_constant(void) {
  putchar('\'');
  for (int c; (c = getchar()) != '\'';) {
    if (c == EOF) {
      exit(1);
    } else if (c == '\\') {
      putchar(c);
      if ((c = getchar()) == EOF) {
        exit(1);
      }
    }
    putchar(c);
  }
  putchar('\'');
}

void read_and_print_string_constant(void) {
  putchar('\"');
  for (int c; (c = getchar()) != '"';) {
    if (c == EOF) {
      exit(1);
    } else if (c == '\\') {
      putchar(c);
      if ((c = getchar()) == EOF) {
        exit(1);
      }
    }
    putchar(c);
  }
  putchar('\"');
}

int main() {
  for (int c; (c = getchar()) != EOF;) {
    switch (c) {
    case '/':
      if ((c = getchar()) == '*') {
        read_comment();
      } else {
        ungetc(c, stdin);
        putchar('/');
      }
      break;
    case '\'':
      read_and_print_char_constant();
      break;
    case '\"':
      read_and_print_string_constant();
      break;
    default:
      putchar(c);
    }
  }
}
