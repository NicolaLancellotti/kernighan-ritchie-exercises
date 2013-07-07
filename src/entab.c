#include "get_line.h"
#include <stdio.h>

#define MAX_LINE 1000
#define DEFAULT_TAB_STOP 8

void init_tab_stops(void);
int next_tab_stop(void);

static void print_substring(char const *line, int left, int right) {
  for (int i = left; i <= right; ++i) {
    putchar(line[i]);
  }
}

static int previous_non_space(char const *line, int index) {
  while (1) {
    if (index < 0) {
      return -1;
    }
    if (line[index] != ' ') {
      return index;
    }
    index--;
  }
}

static void entab_line(char const *line, int len) {
  init_tab_stops();
  int i = 0;
  while (1) {
    int tab_stop;
    do {
      tab_stop = next_tab_stop();
    } while (tab_stop - 1 < len && line[tab_stop - 1] != ' ');

    if (tab_stop > len) {
      tab_stop = len;
    }

    int right = previous_non_space(line, tab_stop - 1);
    if (right != -1) {
      print_substring(line, i, right);
    }
    i = tab_stop;
    if (i == len) {
      return;
    }
    putchar('\t');
  }
}

void entab(void) {
  char line[MAX_LINE];
  int len;
  while ((len = get_line(line, MAX_LINE)) > 0) {
    entab_line(line, len);
  }
}
