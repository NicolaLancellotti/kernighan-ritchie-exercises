#include <stdio.h>
#include <stdlib.h>

enum Error {
  ERROR_COMMENT,
  ERROR_CHAR,
  ERROR_STRING,
  ERROR_PARENTHESES,
  ERROR_BRACKETS,
  ERROR_BRACES,
};

void raise_error(enum Error error) {
  char const *error_string;
  switch (error) {
  case ERROR_COMMENT:
    error_string = "unterminated /* comment";
    break;
  case ERROR_CHAR:
    error_string = "expected '''";
    break;
  case ERROR_STRING:
    error_string = "expected '\"'";
    break;
  case ERROR_PARENTHESES:
    error_string = "extraneous closing ')'";
    break;
  case ERROR_BRACKETS:
    error_string = "extraneous closing ']'";
    break;
  case ERROR_BRACES:
    error_string = "extraneous closing '}'";
    break;
  default:
    error_string = "";
    break;
  }
  printf("error: %s\n", error_string);
  exit(1);
}

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
  raise_error(ERROR_COMMENT);
}

void read_char_constant(void) {
  for (int c; (c = getchar()) != '\'';) {
    if (c == EOF) {
      raise_error(ERROR_CHAR);
    } else if (c == '\\') {
      if ((c = getchar()) == EOF) {
        raise_error(ERROR_CHAR);
      }
    }
  }
}

void read_string_constant(void) {
  for (int c; (c = getchar()) != '"';) {
    if (c == EOF) {
      raise_error(ERROR_STRING);
    } else if (c == '\\') {
      if ((c = getchar()) == EOF) {
        raise_error(ERROR_STRING);
      }
    }
  }
}

int main() {
  int parentheses = 0;
  int brackets = 0;
  int braces = 0;

  for (int c; (c = getchar()) != EOF;) {
    switch (c) {
    case '/':
      if ((c = getchar()) == '*') {
        read_comment();
      } else {
        ungetc(c, stdin);
      }
      break;
    case '\'':
      read_char_constant();
      break;
    case '\"':
      read_string_constant();
      break;
    case '(':
      parentheses++;
      break;
    case '[':
      brackets++;
      break;
    case '{':
      braces++;
      break;
    case ')':
      parentheses--;
      if (parentheses < 0) {
        raise_error(ERROR_PARENTHESES);
      }
      break;
    case ']':
      brackets--;
      if (brackets < 0) {
        raise_error(ERROR_BRACKETS);
      }
      break;
    case '}':
      braces--;
      if (braces < 0) {
        raise_error(ERROR_BRACES);
      }
      break;
    default:
      break;
    }
  }
}
