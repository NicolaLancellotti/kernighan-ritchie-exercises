/*
clang-format off
This version of dcl also handles:
- declarations with function named argument types
- constant pointers
Examples:

char **argv
int (*daytab)[13]
int *daytab[13]
void *comp()
void (*comp)()
char (*(*x())[])()
char (*(*x[3])())[5]

char const **argv
char * const *argv
int (const *daytab)[13]
int const *daytab[13]
void const *comp()
void (const *comp)()
char (const *(const *x())[])()
char (const *(const *x[3])())[5]

void *f(int y, void (*comp)(int x))
void *f(char **argv, int (*daytab)[13], int *daytab[13], void *comp(), void (*comp)(), char (*(*x())[])(), char (*(*x[3])())[5])
void *f(char const * const *argv, int (const *daytab)[13], int const *daytab[13], void const *comp(), void (const *comp)(), char (const *(const *x())[])(), char (const *(const *x[3])())[5])

clang-format on
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, CONST };

int dcl(char *out, char *name);
int dirdcl(char *out, char *name);
int param_dcl(char *out);
int gettoken(void);
void advance(void);

int tokentype;
char token[MAXTOKEN];
int tabs = 0;

int main() {
  while (gettoken() != EOF) {
    char out[1000];
    char datatype[MAXTOKEN];
    char name[MAXTOKEN];

    if (tokentype != NAME) {
      printf("error: expected type\n");
      advance();
      continue;
    }
    strcpy(datatype, token);
    out[0] = '\0';
    if (dcl(out, name)) {
      advance();
      continue;
    }
    if (tokentype != '\n') {
      printf("Syntax error\n");
      advance();
      continue;
    }
    printf("%s: %s %s\n", name, out, datatype);
  }
}

int dcl(char *out, char *name) {
  char pointers_out[100] = "";
  int flag = 1;
  while (flag) {
    switch (gettoken()) {
    case '*':
      strcat(pointers_out, " pointer to");
      break;
    case CONST:
      strcat(pointers_out, " constant");
      if (gettoken() != '*') {
        printf("error: expected *\n");
        return 1;
      }
      strcat(pointers_out, " pointer to");
      break;
    default:
      flag = 0;
    }
  }
  if (dirdcl(out, name)) {
    return 1;
  }
  strcat(out, pointers_out);
  return 0;
}

int dirdcl(char *out, char *name) {
  int type;

  if (tokentype == '(') {
    dcl(out, name);
    if (tokentype != ')') {
      printf("error: missing )\n");
      return 1;
    }
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else {
    printf("error: expected name or (dcl)\n");
    return 1;
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else if (type == BRACKETS) {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    } else {
      ++tabs;
      strcat(out, " function of");
      if (param_dcl(out)) {
        --tabs;
        return 1;
      }
      while (tokentype != ')') {
        if (tokentype != ',') {
          printf("error: missing ,\n");
          --tabs;
          return 1;
        }
        if (param_dcl(out)) {
          --tabs;
          return 1;
        }
      }
      --tabs;
      strcat(out, "\n");
      for (int i = 0; i < tabs; ++i) {
        strcat(out, "\t");
      }
      strcat(out, "returning");
    }
  }
  return 0;
}

int param_dcl(char *out) {
  char param_out[100] = "";
  char param_type[MAXTOKEN];
  char param_name[MAXTOKEN];

  if (gettoken() != NAME) {
    printf("error: expected type\n");
    return 1;
  }
  strcpy(param_type, token);

  if (dcl(param_out, param_name)) {
    return 1;
  }

  strcat(out, "\n");
  for (int i = 0; i < tabs; ++i) {
    strcat(out, "\t");
  }
  strcat(out, param_name);
  strcat(out, ": ");
  strcat(out, param_out);
  strcat(out, " ");
  strcat(out, param_type);
  return 0;
}

int gettoken(void) {
  int c;
  char *p = token;

  while ((c = getchar()) == ' ' || c == '\t') {
  }
  if (c == '(') {
    if ((c = getchar()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetc(c, stdin);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getchar()) != ']';) {
    }
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getchar());) {
      *p++ = c;
    }
    *p = '\0';
    ungetc(c, stdin);

    if (!strcmp(token, "const")) {
      return tokentype = CONST;
    }

    return tokentype = NAME;
  } else
    return tokentype = c;
}

void advance(void) {
  int c;
  while ((c = getchar()) != EOF && c != '\n') {
  }
}
