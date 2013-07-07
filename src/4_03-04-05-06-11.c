#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100

typedef enum {
  ERROR,
  RESULT,
  ANS,
  READ_VAR,
  SET_VAR,
  DUPLICATE,
  SWAP,
  TOP,
  CLEAR,
  NUMBER,
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  NEGATE,
  SIN,
  EXP,
  POW,
} Operator;

Operator getop(char s[]);

void stack_push(double f);

double stack_pop(void);

double stack_top(void);

void stack_clear();

double ans = 0;
double vars[26];

int main() {
  int type;
  double op1, op2;
  char s[MAXOP];

  for (int i = 0; i < 26; ++i) {
    vars[i] = 0;
  }

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case ERROR:
      printf("error: unknown command %s\n", s);
      exit(-1);
    case RESULT:
      ans = stack_pop();
      printf("\t%.8g\n", ans);
      break;
    case ANS:
      stack_push(ans);
      break;
    case READ_VAR:
      stack_push(vars[(s[0] - 'a')]);
      break;
    case SET_VAR:
      vars[s[0] - 'a'] = stack_top();
      break;
    case DUPLICATE:
      stack_push(stack_top());
      break;
    case SWAP:
      op2 = stack_pop();
      op1 = stack_pop();
      stack_push(op2);
      stack_push(op1);
      break;
    case TOP:
      printf("top: %g\n", stack_top());
      break;
    case CLEAR:
      stack_clear();
      break;
    case NUMBER:
      stack_push(atof(s));
      break;
    case ADD:
      stack_push(stack_pop() + stack_pop());
      break;
    case SUB:
      op2 = stack_pop();
      stack_push(stack_pop() - op2);
      break;
    case MUL:
      stack_push(stack_pop() * stack_pop());
      break;
    case DIV:
      op2 = stack_pop();
      if (op2 != 0.0) {
        stack_push(stack_pop() / op2);
      } else {
        printf("error: zero divisor\n");
      }
      break;
    case MOD:
      op2 = stack_pop();
      if (op2 != 0.0) {
        stack_push(fmod(stack_pop(), op2));
      } else {
        printf("error: zero divisor\n");
      }
      break;
    case NEGATE:
      stack_push(-stack_pop());
      break;
    case SIN:
      stack_push(sin(stack_pop()));
      break;
    case EXP:
      stack_push(exp(stack_pop()));
      break;
    case POW:
      op2 = stack_pop();
      stack_push(pow(stack_pop(), op2));
      break;
    }
  }
}

// _____________________________________________________________________________
// Get operator

Operator getop(char s[]) {
  static int previous = ' ';
  s[0] = '\0';
  int c = previous;
  previous = ' ';
  while (c == ' ' || c == '\t') {
    c = getchar();
  }

  switch (c) {
  case '\n':
    return RESULT;
  case '+':
    return ADD;
  case '-':
    return SUB;
  case '*':
    return MUL;
  case '/':
    return DIV;
  case '%':
    return MOD;
  case '=': {
    if (islower(c = getchar())) {
      s[0] = c;
      return SET_VAR;
    } else {
      s[0] = '=';
      s[1] = c;
      s[2] = '\0';
      return ERROR;
    }
  }
  }

  if (islower(c)) {
    int i = 0;
    do {
      s[i++] = c;
      c = getchar();
    } while (islower(c));
    s[i] = '\0';
    if (c != EOF) {
      previous = c;
    }

    int result;
    if (i == 1) {
      result = READ_VAR;
    } else if (!strcmp(s, "ans")) {
      result = ANS;
    } else if (!strcmp(s, "duplicate")) {
      result = DUPLICATE;
    } else if (!strcmp(s, "swap")) {
      result = SWAP;
    } else if (!strcmp(s, "top")) {
      result = TOP;
    } else if (!strcmp(s, "clear")) {
      result = CLEAR;
    } else if (!strcmp(s, "negate")) {
      result = NEGATE;
    } else if (!strcmp(s, "sin")) {
      result = SIN;
    } else if (!strcmp(s, "exp")) {
      result = EXP;
    } else if (!strcmp(s, "pow")) {
      result = POW;
    } else {
      result = ERROR;
    }

    if (result != READ_VAR && result != SET_VAR && result != ERROR) {
      s[0] = '\0';
    }
    return result;
  }

  int i = 0;
  if (isdigit(c)) {
    do {
      s[i++] = c;
      c = getchar();
    } while (isdigit(c));
    s[i] = '\0';
    if (c != EOF) {
      previous = c;
    }
    return NUMBER;
  } else {
    s[i++] = c;
    s[i] = '\0';
    return ERROR;
  }
}

// _____________________________________________________________________________
// Stack

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void stack_push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else
    printf("error: stack full, can't push %g\n", f);
}

double stack_pop(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

double stack_top(void) {
  if (sp > 0) {
    return val[sp - 1];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

void stack_clear() { sp = 0; }
