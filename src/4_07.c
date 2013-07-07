#include <stdio.h>
#include <string.h>

int getch(void);
void ungetch(int c);
void ungets(char const *s);

int main() {
  char const s[] = "abc";
  ungets(s);
  for (int c; (c = getch()) != EOF;) {
    putchar(c);
  }
}

// _____________________________________________________________________________
// Char buffer

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

void ungets(char const *s) {
  size_t i = strlen(s);
  if (bufp + i - 1 >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    while (i > 0) {
      ungetch(s[--i]);
    }
  }
}
