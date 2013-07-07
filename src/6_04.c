#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_word(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getchar())) {
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

struct TNode {
  char *word;
  int count;
  struct TNode *left;
  struct TNode *right;
};

struct TNode *add_tree(struct TNode *p, char *w) {
  int cond;
  if (p == NULL) {
    p = malloc(sizeof(struct TNode));
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;
  } else if (cond < 0) {
    p->left = add_tree(p->left, w);
  } else {
    p->right = add_tree(p->right, w);
  }
  return p;
}

struct WordList {
  char *word;
  struct WordList *next;
};

struct TNodeFrequency {
  int count;
  struct WordList *word_list;
  struct TNodeFrequency *left;
  struct TNodeFrequency *right;
};

struct TNodeFrequency *add_tree_frequency(struct TNodeFrequency *p,
                                          struct TNode const *node) {
  if (p == NULL) {
    p = malloc(sizeof(struct TNodeFrequency));
    p->count = node->count;
    p->left = p->right = NULL;
    p->word_list = malloc(sizeof(struct WordList));
    p->word_list->word = strdup(node->word);
    p->word_list->next = NULL;
  } else if (p->count == node->count) {
    struct WordList *word_list = p->word_list;
    p->word_list = malloc(sizeof(struct WordList));
    p->word_list->word = strdup(node->word);
    p->word_list->next = word_list;
  } else if (node->count < p->count) {
    p->left = add_tree_frequency(p->left, node);
  } else {
    p->right = add_tree_frequency(p->right, node);
  }
  return p;
}

void tree_print(const struct TNodeFrequency *p) {
  if (p != NULL) {
    tree_print(p->right);
    for (struct WordList *list = p->word_list; list != NULL;
         list = list->next) {
      printf("%4d  %s\n", p->count, list->word);
    }
    tree_print(p->left);
  }
}

struct TNodeFrequency *transform(struct TNode const *p,
                                 struct TNodeFrequency *node) {
  if (p != NULL) {
    node = transform(p->left, node);
    node = add_tree_frequency(node, p);
    node = transform(p->right, node);
  }
  return node;
}

#define MAXWORD 100

int main() {
  struct TNode *root = NULL;
  char word[MAXWORD];

  while (get_word(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      root = add_tree(root, word);
    }
  }

  struct TNodeFrequency *rootFrequency = transform(root, NULL);
  tree_print(rootFrequency);
}
