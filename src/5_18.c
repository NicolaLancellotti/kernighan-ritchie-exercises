/*
Examples:

char **argv
int (*daytab)[13]
int *daytab[13]
void *comp()
void (*comp)()
char (*(*x())[])()
char (*(*x[3])())[5]
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int dcl(void);
int dirdcl(void);
int gettoken(void);
void advance(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main() {
  while (gettoken() != EOF) {
    if (tokentype != NAME) {
      printf("error: expected type\n");
      advance();
      continue;
    }
    strcpy(datatype, token);
    out[0] = '\0';
    if (dcl()) {
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

int dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';) {
    ns++;
  }
  if (dirdcl()) {
    return 1;
  }
  while (ns-- > 0) {
    strcat(out, " pointer to");
  }
  return 0;
}

int dirdcl(void) {
  int type;

  if (tokentype == '(') {
    dcl();
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
  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
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
    return tokentype = NAME;
  } else
    return tokentype = c;
}

void advance(void) {
  int c;
  while ((c = getchar()) != EOF && c != '\n') {
  }
}
