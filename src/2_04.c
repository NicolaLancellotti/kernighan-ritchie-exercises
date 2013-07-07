#include <assert.h>
#include <string.h>

void squeze(char s1[], char const s2[]) {
  int i, j;
  for (i = j = 0; s1[i] != '\0'; ++i) {
    int found = 0;
    for (int k = 0; s2[k]; ++k) {
      if (s1[i] == s2[k]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      s1[j++] = s1[i];
    }
  }
  s1[j] = '\0';
}

int main() {
  char s[] = "abcdef";
  squeze(s, "acdf");
  assert(!strcmp(s, "be"));
}
