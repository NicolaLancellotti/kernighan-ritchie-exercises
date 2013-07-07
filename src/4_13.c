#include <assert.h>
#include <string.h>

void reverse(char s[], int i, int j) {
  if (i < j) {
    reverse(s, i + 1, j - 1);
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}

int main() {
  char s[] = "abc";
  reverse(s, 0, strlen(s) - 1);
  assert(!strcmp(s, "cba"));
}
