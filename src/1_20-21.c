
#define DEFAULT_TAB_STOP 8

int last_tab_stop = 0;

void init_tab_stops(void) { last_tab_stop = 0; }

int next_tab_stop(void) { return last_tab_stop += DEFAULT_TAB_STOP; }

int main() {
#ifdef DETAB
  void detab(void);
  detab();
#elifdef ENTAB
  void entab(void);
  entab();
#endif
}
