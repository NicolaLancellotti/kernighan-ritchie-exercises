#include <stdio.h>

int main() {
  int const lower = 0, upper = 300, step = 20;
  float fahr = upper;
  printf("  F      C\n");
  while (fahr >= lower) {
    float celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr - step;
  }
}
