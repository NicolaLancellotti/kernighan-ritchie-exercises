#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

void undef(char const *name) {
  unsigned hashval = hash(name);
  struct nlist *first = hashtab[hashval];

  if (first && strcmp(first->name, name) == 0) {
    struct nlist *toDelete = first;
    hashtab[hashval] = toDelete->next;
    free(toDelete->name);
    free(toDelete->defn);
    free(toDelete);
    return;
  }

  for (struct nlist *np = first; np != NULL; np = np->next) {
    if (np->next && strcmp(np->next->name, name) == 0) {
      struct nlist *toDelete = np->next;
      np->next = toDelete->next;
      free(toDelete->name);
      free(toDelete->defn);
      free(toDelete);
      return;
    }
  }
}

int main() {
  install("A", "value");
  assert(lookup("A"));
  undef("A");
  assert(!lookup("A"));
}
