#include <stdio.h>
#include <stdlib.h>

int tab_stop = 8;
int tab_stop_init = 0;
int last_tab_stop = 0;

void init_tab_stops(void) { last_tab_stop = tab_stop_init; }

int next_tab_stop(void) { return last_tab_stop += tab_stop; }

int main(int argc, char const *argv[]) {
  while (--argc > 0) {
    char const *arg = *++argv;
    switch (*arg++) {
    case '-':
      tab_stop_init = atoi(arg);
      if (tab_stop_init < 0) {
        printf("bad tab stop spec\n");
        exit(1);
      }
      break;
    case '+':
      tab_stop = atoi(arg);
      if (tab_stop < 1) {
        printf("bad tab stop spec\n");
        exit(1);
      }
      break;
    }
  }
#ifdef DETAB
  void detab(void);
  detab();
#elifdef ENTAB
  void entab(void);
  entab();
#endif
}
