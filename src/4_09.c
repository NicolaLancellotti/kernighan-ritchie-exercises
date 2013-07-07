#include "getch.h"
#include <assert.h>
#include <stdio.h>

int main() {
  ungetch('a');
  ungetch(EOF);
  ungetch('b');
  assert(getch() == 'b');
  assert(getch() == EOF);
  assert(getch() == 'a');
}
