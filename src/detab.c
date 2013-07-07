#include "get_line.h"
#include <stdio.h>

#define MAX_LINE 1000
#define DEFAULT_TAB_STOP 8

void init_tab_stops(void);
int next_tab_stop(void);

static int print_substring(char const *line, int left, int right) {
  for (int i = left; i <= right; ++i) {
    putchar(line[i]);
  }
  return right - left + 1;
}

static int print_spaces(int count) {
  for (int i = 0; i < count; ++i) {
    putchar(' ');
  }
  return count;
}

static int next_tab(char const *line, int index) {
  while (1) {
    switch (line[index]) {
    case '\0':
      return -1;
    case '\t':
      return index;
    default:
      index++;
    }
  }
}

static void detab_line(char const *line, int len) {
  init_tab_stops();
  int i = 0;
  int count = 0;
  while (i < len) {
    int tab = next_tab(line, i);
    if (tab == -1) {
      print_substring(line, i, len - 1);
      return;
    }

    int tab_stop;
    do {
      tab_stop = next_tab_stop();
    } while (tab >= tab_stop);

    count += print_substring(line, i, tab - 1);
    count += print_spaces(tab_stop - count);
    i = tab + 1;
  }
}

void detab(void) {
  char line[MAX_LINE];
  int len;
  while ((len = get_line(line, MAX_LINE)) > 0) {
    detab_line(line, len);
  }
}
