/*
argv * * char
daytab * [13] int
daytab [13] * int
comp () * void
comp * () void
x () * [] * () char
x [3] * () * [5] char
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main() {
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    int pointer = 0;
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
        if (pointer) {
          sprintf(temp, "(%s)", out);
          strcpy(out, temp);
          pointer = 0;
        }
        strcat(out, token);
      } else if (type == '*') {
        sprintf(temp, "*%s", out);
        strcpy(out, temp);
        pointer = 1;
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else {
        printf("invalid input at %s\n", token);
      }
    }
    printf("%s\n", out);
  }
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
