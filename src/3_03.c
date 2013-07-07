#include <assert.h>
#include <string.h>

#define LENGTH 80

void expand(char const s1[], char s2[]) {
  int i1 = 0, i2 = 0;
  while (s1[i1]) {
    if (s1[i1 + 1] == '-') {
      int start = s1[i1];
      int end = s1[i1 + 2];
      int lowercase = start >= 'a' && start <= 'z' && end >= 'a' && end <= 'z';
      int uppercase = start >= 'A' && start <= 'Z' && end >= 'A' && end <= 'Z';
      int numbers = start >= '0' && start <= '9' && end >= '0' && end <= '9';
      if ((lowercase || uppercase || numbers) && (start <= end)) {
        while (start <= end) {
          s2[i2++] = start++;
        }
        i1 += s1[i1 + 3] == '-' ? 2 : 3;
        continue;
      }
    }
    s2[i2++] = s1[i1++];
  }
  s2[i2] = '\0';
}

int main() {
  char const s1[LENGTH] = "-a-z0-9a-b-c";
  char s2[LENGTH];
  expand(s1, s2);
  assert(!strcmp(s2, "-abcdefghijklmnopqrstuvwxyz0123456789abbc"));
}
