#include <stdio.h>

#define HISTOGRAM_SIZE 10

int make_histogram(int histogram[]) {
  for (int i = 0; i < HISTOGRAM_SIZE; ++i) {
    histogram[i] = 0;
  }

  int max_frequency = 0;
  int length = 0;
  for (int c; (c = getchar()) != EOF;) {
    int end_word = c == ' ' || c == '\n' || c == '\t';
    if (!end_word) {
      length++;
    } else if (length) {
      if (length > HISTOGRAM_SIZE) {
        length = HISTOGRAM_SIZE;
      }
      int frequency = ++histogram[length - 1];
      if (frequency > max_frequency) {
        max_frequency = frequency;
      }
      length = 0;
    }
  }
  return max_frequency;
}

void print_histogram(int const histogram[], int max_frequency) {
  printf("\n\n");
  for (int i = max_frequency; i > 0; --i) {
    printf("%4d|", i);
    for (int j = 0; j < HISTOGRAM_SIZE; ++j) {
      printf(histogram[j] >= i ? " * " : "   ");
    }
    putchar('\n');
  }
  printf("    |");
  for (int i = 0; i < HISTOGRAM_SIZE; ++i) {
    printf("---");
  }
  printf("\n     ");
  for (int i = 0; i < HISTOGRAM_SIZE - 1; ++i) {
    printf(" %d ", i + 1);
  }
  printf(" >=%d\n", HISTOGRAM_SIZE);
}

int main() {
  int histogram[HISTOGRAM_SIZE];
  int max_frequency = make_histogram(histogram);
  print_histogram(histogram, max_frequency);
}
