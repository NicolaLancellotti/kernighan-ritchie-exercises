#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 8
#define MAX_TAB_STOPS 100

int tab_stops[MAX_TAB_STOPS];
int tab_stops_length = 0;

int tab_stops_index = 0;
int last_tab_stop = 0;

void init_tab_stops(void) {
  tab_stops_index = 0;
  last_tab_stop = 0;
}

int next_tab_stop(void) {
  if (tab_stops_index < tab_stops_length) {
    return last_tab_stop = tab_stops[tab_stops_index++];
  }

  if (tab_stops_length == 0) {
    return last_tab_stop += DEFAULT_TAB_STOP;
  } else {
    return last_tab_stop += 2;
  }
}

int main(int argc, char const *argv[]) {
  for (int i = 1; i < argc; ++i) {
    int value = atoi(argv[i]);
    if ((value <= 0) ||
        (tab_stops_length > 0 && value <= tab_stops[tab_stops_length - 1])) {
      printf("bad tab stop spec\n");
      exit(1);
    }
    tab_stops[tab_stops_length++] = value;
  }
#ifdef DETAB
  void detab(void);
  detab();
#elifdef ENTAB
  void entab(void);
  entab();
#endif
}
