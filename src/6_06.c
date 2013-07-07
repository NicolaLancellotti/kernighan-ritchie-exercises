#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_word(char *word, int lim) {
  int c;
  char *w = word;

  if (isspace(c = getchar())) {
    *w++ = c;
    *w = '\0';
    return c;
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

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char const *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *lookup(char const *s) {
  for (struct nlist *np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np;
    }
  }
  return NULL;
}

struct nlist *install(char const *name, char const *defn) {
  struct nlist *np;
  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL) {
      return NULL;
    }
    unsigned hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free((void *)np->defn);
  }
  if ((np->defn = strdup(defn)) == NULL) {
    return NULL;
  }
  return np;
}

#define MAXWORD 100

void get_word_and_print_it_with_spaces(char word[]) {
  do {
    if (get_word(word, MAXWORD) == EOF) {
      exit(1);
    } else if (isspace(word[0])) {
      putchar(word[0]);
    } else {
      printf("%s", word);
      break;
    }
  } while (1);
}

int main() {
  char word[MAXWORD];
  char defn[MAXWORD];
  struct nlist *p;
  while (get_word(word, MAXWORD) != EOF) {
    if (strcmp(word, "#define") == 0) {
      printf("#define");
      get_word_and_print_it_with_spaces(word);
      get_word_and_print_it_with_spaces(defn);
      install(word, defn);
    } else if ((p = lookup(word)) != NULL) {
      printf("%s", p->defn);
    } else {
      printf("%s", word);
    }
  }
}
