#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

int main() {
  printf("char min: %d\n", CHAR_MIN);
  printf("char max: %d\n", CHAR_MAX);
  printf("unsigned char max: %u\n", UCHAR_MAX);

  printf("short min: %d\n", SHRT_MIN);
  printf("short max: %d\n", SHRT_MAX);
  printf("unsigned short max: %u\n", USHRT_MAX);

  printf("int min: %d\n", INT_MIN);
  printf("int max: %d\n", INT_MAX);
  printf("unsigned int max: %u\n", UINT_MAX);

  printf("long min: %ld\n", LONG_MIN);
  printf("long max: %ld\n", LONG_MAX);
  printf("unsigned long max: %lu\n", ULONG_MAX);

  putchar('\n');

  short s = 0;
  while (s >= 0) {
    s++;
  }
  printf("short min: %d\n", s);
  --s;
  printf("short max: %d\n", s);

  printf("unsigned short max: %d\n", (unsigned short)-1);

  putchar('\n');

  printf("float max: %f\n", FLT_MAX);
  float float_max =
      powf(2, FLT_MAX_EXP - 1) * (2 - 2 * powf(0.5, FLT_MANT_DIG));
  printf("float max: %f\n", float_max);

  printf("double max: %f\n", DBL_MAX);
  double double_max =
      pow(2, DBL_MAX_EXP - 1) * (2 - 2 * pow(0.5, DBL_MANT_DIG));
  printf("double max: %f\n", double_max);
}
