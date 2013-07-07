#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_word(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getchar()) && c != '\n') {
  }

  if (c != EOF) {
    *w++ = c;
  }

  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; ++w) {
    if (!isalnum(*w = getchar())) {
      ungetc(*w, stdin);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

struct LineList {
  int line;
  struct LineList *next;
};

struct TNode {
  char *word;
  struct LineList *first;
  struct LineList *last;
  struct TNode *left;
  struct TNode *right;
};

struct TNode *add_tree(struct TNode *p, char *w, int count) {
  int cond;
  if (p == NULL) {
    p = malloc(sizeof(struct TNode));
    p->word = strdup(w);
    p->left = p->right = NULL;
    p->first = p->last = malloc(sizeof(struct LineList));
    p->first->line = count;
    p->first->next = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->last->next = malloc(sizeof(struct LineList));
    p->last->next->line = count;
    p->last->next->next = NULL;
    p->last = p->last->next;
  } else if (cond < 0) {
    p->left = add_tree(p->left, w, count);
  } else {
    p->right = add_tree(p->right, w, count);
  }
  return p;
}

void tree_print(struct TNode const *p) {
  if (p != NULL) {
    tree_print(p->left);
    printf("\n%s: \n\t", p->word);
    for (struct LineList *lineList = p->first; lineList != NULL;
         lineList = lineList->next) {
      printf("%d ", lineList->line);
    }
    tree_print(p->right);
  }
}

char const *const words_to_remove[] = {"and", "the"};

#define N_WORDS_TO_REMOVE (sizeof words_to_remove / sizeof words_to_remove[0])

int bin_search(char *word, char const *const words_to_remove[], int n) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    int cond;
    if ((cond = strcmp(word, words_to_remove[mid])) < 0) {
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

int main() {
  struct TNode *root = NULL;
  char word[MAXWORD];
  int line = 1;

  while (get_word(word, MAXWORD) != EOF) {
    if (word[0] == '\n') {
      line++;
      continue;
    }
    if (isalpha(word[0]) &&
        bin_search(word, words_to_remove, N_WORDS_TO_REMOVE) == -1) {
      root = add_tree(root, word, line);
    }
  }
  tree_print(root);
  putchar('\n');
}
