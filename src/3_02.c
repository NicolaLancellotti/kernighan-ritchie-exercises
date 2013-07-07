#include <assert.h>
#include <string.h>

#define LENGTH 80

void escape(char s[], char const t[]) {
  int i = 0, j = 0;
  while (t[i]) {
    switch (t[i]) {
    case '\n':
      s[j++] = '\\';
      s[j++] = 'n';
      break;
    case '\t':
      s[j++] = '\\';
      s[j++] = 't';
      break;
    default:
      s[j++] = t[i];
      break;
    }
    i++;
  }
  s[j] = t[i];
}

void unescape(char s[], char const t[]) {
  int i = 0, j = 0;
  while (t[i]) {
    switch (t[i]) {
    case '\\':
      if (t[i + 1] == 'n') {
        s[j++] = '\n';
        i++;
        break;
      } else if (t[i + 1] == 't') {
        s[j++] = '\t';
        i++;
        break;
      }
    default:
      s[j++] = t[i];
      break;
    }
    i++;
  }
  s[j] = t[i];
}

int main() {
  char const s[LENGTH] = "abc\t123\nABC";

  char escaped[LENGTH];
  escape(escaped, s);
  assert(!strcmp(escaped, "abc\\t123\\nABC"));

  char unescaped[LENGTH];
  unescape(unescaped, escaped);
  assert(!strcmp(unescaped, s));
}
