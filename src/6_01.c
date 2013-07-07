#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int get_word(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getchar())) {
  }

  // String constants
  if (c == '"') {
    *w++ = c;
    while ((c = getchar()) != '"') {
      if (c == EOF) {
        exit(1);
      } else if (c == '\\') {
        *w++ = c;
        if ((c = getchar()) == EOF) {
          exit(1);
        }
      }
      *w++ = c;
    }
    *w++ = c;
    *w = '\0';
    return c;
  }

  // Comments
  if (c == '/') {
    if ((c = getchar()) != '*') {
      ungetc(c, stdin);
      *w++ = '/';
      *w = '\0';
      return word[0];
    }

    while (1) {
      while ((c = getchar()) != '*') {
        if (c == EOF) {
          exit(1);
        }
      }
      if ((c = getchar()) == '/') {
        return get_word(word, lim);
      }
      ungetc(c, stdin);
    }
  }

  // Preprocessor directives
  if (c == '#') {
    *w++ = c;
    for (; --lim > 0; ++w) {
      if (!isalpha(*w = getchar())) {
        ungetc(*w, stdin);
        break;
      }
    }
    *w = '\0';
    return word[0];
  }

  if (c != EOF) {
    *w++ = c;
  }

  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; ++w) {
    if (!isalnum(*w = getchar()) && *w != '_' /* underscores */) {
      ungetc(*w, stdin);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

int main() {
  int const lim = 20;
  char word[lim];
  get_word(word, lim);
  printf("%s", word);
}
