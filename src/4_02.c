#include <assert.h>
#include <ctype.h>
#include <math.h>

int atoi(char const s[]) {
  int i = 0;
  int sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }

  int val = 0;
  for (; isdigit(s[i]); ++i) {
    val = 10 * val + (s[i] - '0');
  }

  return sign * val;
}

double atof(char const s[]) {
  int i = 0;
  for (; isspace(s[i]); ++i) {
  }
  int sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }

  double val = 0.0;
  for (; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
  }

  if (s[i] == '.') {
    i++;
  }
  int power = 1.0;
  for (; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  int exponent = 0;
  if (s[i] == 'e' || s[i] == 'E') {
    i++;
    exponent = atoi(s + i);
  }

  return sign * val / power * pow(10, exponent);
}

int main() { assert(atof("-1.23E-2") == -0.0123); }
