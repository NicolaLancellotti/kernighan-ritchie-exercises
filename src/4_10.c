#include "get_line.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double f);
double pop(void);

int main() {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        printf("error: zero divisor\n");
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
}

// _____________________________________________________________________________
// Get operator

#define MAXLINE 200
char line[MAXLINE] = "\0";
int line_index = 0;

int getop(char s[]) {
  if (line[line_index] == '\0') {
    if (get_line(line, MAXLINE) <= 0) {
      return EOF;
    }
    line_index = 0;
  }

  int c;
  while ((s[0] = c = line[line_index++]) == ' ' || c == '\t') {
  }
  s[1] = '\0';
  if (!isdigit(c) && c != '.') {
    return c;
  }
  int i = 0;
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = line[line_index++])) {
    }
  }

  if (c == '.') {
    while (isdigit(s[++i] = c = line[line_index++])) {
    }
  }
  s[i] = '\0';
  if (c != EOF) {
    line_index--;
  }
  return NUMBER;
}

// _____________________________________________________________________________
// Stack

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}
