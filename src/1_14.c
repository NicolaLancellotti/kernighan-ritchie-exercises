#include <stdio.h>

#define HISTOGRAM_FIRST_CHAR ' '
#define HISTOGRAM_SIZE (127 - HISTOGRAM_FIRST_CHAR)

int make_histogram(int histogram[]) {
  for (int i = 0; i < HISTOGRAM_SIZE; ++i) {
    histogram[i] = 0;
  }
  int max_frequency = 0;
  for (int c; (c = getchar()) != EOF;) {
    if (c >= HISTOGRAM_FIRST_CHAR &&
        c < HISTOGRAM_SIZE + HISTOGRAM_FIRST_CHAR) {
      int frequency = ++histogram[c - HISTOGRAM_FIRST_CHAR];
      if (frequency > max_frequency) {
        max_frequency = frequency;
      }
    }
  }
  return max_frequency;
}

void print_histogram(int const histogram[], int max_frequency, int start,
                     int end) {
  printf("\n\n");
  for (int i = max_frequency; i > 0; --i) {
    printf("%4d|", i);
    for (int j = start; j < end; ++j) {
      printf(histogram[j] >= i ? " * " : "   ");
    }
    putchar('\n');
  }
  printf("    |");
  for (int i = start; i < end; ++i) {
    printf("---");
  }
  printf("\n     ");
  for (int i = start; i < end; ++i) {
    printf(" %c ", (char)(i + HISTOGRAM_FIRST_CHAR));
  }
  putchar('\n');
}

int main() {
  int histogram[HISTOGRAM_SIZE];
  int max_frequency = make_histogram(histogram);
  int offset = HISTOGRAM_SIZE / 3;
  print_histogram(histogram, max_frequency, 0, offset);
  print_histogram(histogram, max_frequency, offset, offset * 2);
  print_histogram(histogram, max_frequency, offset * 2, HISTOGRAM_SIZE);
}
