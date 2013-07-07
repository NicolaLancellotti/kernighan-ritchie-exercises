#include "get_line.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines) {
  int len;
  char *p, line[MAXLEN];
  int nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = malloc(len)) == NULL) {
      return -1;
    } else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

void writelines(char const *const lineptr[], int nlines) {
  for (int i = 0; i < nlines; ++i) {
    printf("%s\n", lineptr[i]);
  }
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void qsort_1(void *v[], int left, int right,
             int (*comp)(void const *lhs, void const *rhs, void const *options),
             void const *options) {
  if (left >= right) {
    return;
  }
  swap(v, left, (left + right) / 2);
  int last = left;
  for (int i = left + 1; i <= right; ++i) {
    if ((*comp)(v[i], v[left], options) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort_1(v, left, last - 1, comp, options);
  qsort_1(v, last + 1, right, comp, options);
}

int numcmp(char const *s1, char const *s2) {
  double v1 = atof(s1);
  double v2 = atof(s2);
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

int str_cmp_fold(char const *lhs, char const *rhs) {
  for (; tolower(*lhs) == tolower(*rhs); ++lhs, ++rhs) {
    if (*lhs == '\0') {
      return 0;
    }
  }
  return tolower(*lhs) - tolower(*rhs);
}

int directory_cmp_impl(char const *lhs, char const *rhs, int fold) {
  while (*lhs && !isalnum(*lhs) && !isblank(*lhs)) {
    lhs++;
  }
  while (*rhs && !isalnum(*rhs) && !isblank(*rhs)) {
    rhs++;
  }

  while ((!fold && *lhs == *rhs) || (fold && tolower(*lhs) == tolower(*rhs))) {
    if (*lhs == '\0') {
      return 0;
    }
    lhs++;
    while (*lhs && !isalnum(*lhs) && !isblank(*lhs)) {
      lhs++;
    }
    rhs++;
    while (*rhs && !isalnum(*rhs) && !isblank(*rhs)) {
      rhs++;
    }
  }
  return fold ? tolower(*lhs) - tolower(*rhs) : *lhs - *rhs;
}

int directory_cmp(char const *lhs, char const *rhs) {
  return directory_cmp_impl(lhs, rhs, 0);
}

int directory_cmp_fold(char const *lhs, char const *rhs) {
  return directory_cmp_impl(lhs, rhs, 1);
}

typedef struct SortOptions {
  int numeric;
  int fold;
  int directory;
  int reverse;
} SortOptions;

int comp(void const *s1, void const *s2, const SortOptions *options) {
  int (*f)(void const *, void const *);
  if (options->numeric) {
    f = (int (*)(void const *, void const *))numcmp;
  } else if (options->directory) {
    f = (int (*)(void const *, void const *))(options->fold ? directory_cmp_fold
                                                            : directory_cmp);
  } else {
    f = (int (*)(void const *, void const *))(options->fold ? str_cmp_fold
                                                            : strcmp);
  }
  return options->reverse ? -1 * f(s1, s2) : f(s1, s2);
}

int main(int argc, char const *argv[]) {
  SortOptions options = {.numeric = 0, .fold = 0, .directory = 0, .reverse = 0};
  for (int i = 1; i < argc; ++i) {
    if (*argv[i] == '-') {
      while (*++argv[i]) {
        switch (*argv[i]) {
        case 'n':
          options.numeric = 1;
          break;
        case 'f':
          options.fold = 1;
          break;
        case 'd':
          options.directory = 1;
          break;
        case 'r':
          options.reverse = 1;
          break;
        }
      }
    }
  }
  if (options.numeric && options.directory) {
    return 1;
  }
  int nlines;
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort_1((void **)lineptr, 0, nlines - 1,
            (int (*)(void const *, void const *, void const *))comp,
            (void *)&options);
    writelines((char const *const *)lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}
