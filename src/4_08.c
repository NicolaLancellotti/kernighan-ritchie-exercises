#include <assert.h>
#include <stdio.h>

int getch(void);
void ungetch(int c);

int main() {
  ungetch('a');
  assert(getch() == 'a');
}

// _____________________________________________________________________________
// Char buffer

char buffer = EOF;

int getch(void) {
  if (buffer == EOF) {
    return getchar();
  } else {
    int tmp = buffer;
    buffer = EOF;
    return tmp;
  }
}

void ungetch(int c) {
  if (buffer == EOF) {
    buffer = c;
  } else {
    printf("ungetch: too many characters\n");
  }
}
