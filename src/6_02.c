#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_word(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getchar())) {
  }

  // String constants
  if (c == '"') {
    *w++ = c;
    while ((c = getchar()) != '"') {
      if (c == EOF) {
        exit(1);
      } else if (c == '\\') {
        *w++ = c;
        if ((c = getchar()) == EOF) {
          exit(1);
        }
      }
      *w++ = c;
    }
    *w++ = c;
    *w = '\0';
    return c;
  }

  // Comments
  if (c == '/') {
    if ((c = getchar()) != '*') {
      ungetc(c, stdin);
      *w++ = '/';
      *w = '\0';
      return word[0];
    }

    while (1) {
      while ((c = getchar()) != '*') {
        if (c == EOF) {
          exit(1);
        }
      }
      if ((c = getchar()) == '/') {
        return get_word(word, lim);
      }
      ungetc(c, stdin);
    }
  }

  // Preprocessor directives
  if (c == '#') {
    *w++ = c;
    for (; --lim > 0; ++w) {
      if (!isalpha(*w = getchar())) {
        ungetc(*w, stdin);
        break;
      }
    }
    *w = '\0';
    return word[0];
  }

  if (c != EOF) {
    *w++ = c;
  }

  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; ++w) {
    if (!isalnum(*w = getchar()) && *w != '_' /* underscores */) {
      ungetc(*w, stdin);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

struct WordList {
  char *word;
  struct WordList *next;
};

struct TNode {
  struct WordList *word_list;
  struct TNode *left;
  struct TNode *right;
};

struct TNode *add_tree(struct TNode *p, char const *w, int count) {
  int cond;
  if (p == NULL) {
    p = malloc(sizeof(struct TNode));
    p->word_list = malloc(sizeof(struct WordList));
    p->word_list->word = strdup(w);
    p->word_list->next = NULL;
    p->left = p->right = NULL;
  } else if ((cond = strncmp(w, p->word_list->word, count)) == 0) {
    struct WordList *wordList = p->word_list;
    p->word_list = malloc(sizeof(struct WordList));
    p->word_list->word = strdup(w);
    p->word_list->next = wordList;
  } else if (cond < 0) {
    p->left = add_tree(p->left, w, count);
  } else {
    p->right = add_tree(p->right, w, count);
  }
  return p;
}

void treeprint(struct TNode const *p, int count) {
  if (p != NULL) {
    treeprint(p->left, count);
    printf("\n%.*s:\n", count, p->word_list->word);
    for (struct WordList *list = p->word_list; list != NULL;
         list = list->next) {
      printf("%s\n", list->word);
    }
    treeprint(p->right, count);
  }
}

char const *const keys[] = {
    "auto",     "break",  "case",    "char",   "const",    "continue",
    "default",  "do",     "double",  "else",   "enum",     "extern",
    "float",    "for",    "goto",    "if",     "int",      "long",
    "register", "return", "short",   "signed", "sizeof",   "static",
    "struct",   "switch", "typedef", "union",  "unsigned", "void",
    "volatile", "while"};

#define NKEYS (sizeof keys / sizeof keys[0])

int bin_search(char const *word, char const *const keys[], int n) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    int cond;
    if ((cond = strcmp(word, keys[mid])) < 0) {
      high = mid - 1;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

#define MAXWORD 100

int main(int argc, char const *argv[]) {
  int count = argc == 2 ? atoi(argv[1]) : 6;
  struct TNode *root = NULL;
  char word[MAXWORD];

  while (get_word(word, MAXWORD) != EOF) {
    if (isalpha(word[0]) && bin_search(word, keys, NKEYS) == -1) {
      root = add_tree(root, word, count);
    }
  }
  treeprint(root, count);
}
