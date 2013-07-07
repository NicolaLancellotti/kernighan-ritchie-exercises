#include <stdio.h>

#define MAXLINE 200
#define NUMBER '0'
#define ERROR '1'

int getop(char s[], double *number);
void push(double f);
double pop(void);

int main() {
  int type;
  double op;
  char s[MAXLINE];

  while ((type = getop(s, &op)) != EOF) {
    switch (type) {
    case NUMBER:
      push(op);
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op = pop();
      push(pop() - op);
      break;
    case '/':
      op = pop();
      if (op != 0.0) {
        push(pop() / op);
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

int getop(char s[], double *number) {
  static char c = '\0';
  if (c == '\n') {
    c = '\0';
    return '\n';
  }
  if (scanf("%s%c", s, &c) != 2) {
    return EOF;
  }

  if (sscanf(s, "%lf", number) == 1) {
    return NUMBER;
  }

  if (s[1] == '\0') {
    return s[0];
  }

  return ERROR;
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
