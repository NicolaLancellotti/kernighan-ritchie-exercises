#include <stdio.h>

float fahrenheit_to_celsius(float fahr) { return (5.0 / 9.0) * (fahr - 32.0); }

int main() {
  int const lower = 0, upper = 300, step = 20;
  float fahr = lower;
  printf("  F      C\n");
  while (fahr <= upper) {
    float celsius = fahrenheit_to_celsius(fahr);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
