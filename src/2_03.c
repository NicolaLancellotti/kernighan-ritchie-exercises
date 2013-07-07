#include <assert.h>

int hexadecimal_to_decimal(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } else {
    return -1;
  }
}

int htoi(char s[]) {
  int i = 0;
  if (s[0] == '0' && (s[1] == 'X' || s[1] == 'x')) {
    i = i + 2;
  }
  int decimal = 0;
  while (s[i]) {
    int hexadecimal = hexadecimal_to_decimal(s[i]);
    if (hexadecimal == -1) {
      return -1;
    }
    decimal = decimal * 16 + hexadecimal;
    i++;
  }
  return decimal;
}

int main() {
  assert(htoi("0") == 0);
  assert(htoi("1") == 1);
  assert(htoi("9") == 9);
  assert(htoi("a") == 0xa);
  assert(htoi("A") == 0xa);
  assert(htoi("f") == 0xf);
  assert(htoi("F") == 0xf);
  assert(htoi("0XC8") == 0XC8);
  assert(htoi("0xC8") == 0xC8);
}
