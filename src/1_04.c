#include <stdio.h>

int main() {
  int const lower = 0, upper = 300, step = 20;
  float celsius = lower;
  printf("  C      F\n");
  while (celsius <= upper) {
    float fahr = celsius * (9.0 / 5.0) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
