#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

#define NALLOC 1024

void free_1(void *ap) {
  if (!ap) {
    return;
  }
  Header *p;
  Header *bp = (Header *)ap - 1;
  if (bp->s.size == 0) {
    exit(1);
  }
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break;
    }
  }

  if (p->s.ptr != &base && bp < p->s.ptr && bp + bp->s.size > p->s.ptr) {
    exit(2);
  }

  if (bp + bp->s.size == p->s.ptr) {
    if (bp->s.size > UINT_MAX - p->s.ptr->s.size) {
      exit(3);
    }
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if (p + p->s.size == bp) {
    if (p->s.size > UINT_MAX - bp->s.size) {
      exit(4);
    }
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

static Header *morecore(unsigned nu) {
  char *sbrk(int);

  if (nu < NALLOC) {
    nu = NALLOC;
  }
  char *cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) {
    return NULL;
  }
  Header *up = (Header *)cp;
  up->s.size = nu;
  free_1((void *)(up + 1));
  return freep;
}

void *malloc_1(unsigned nbytes) {
  if (nbytes == 0 || nbytes > UINT_MAX - sizeof(Header)) {
    return NULL;
  }
  Header *p, *prevp;
  unsigned nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }

  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits) {
        prevp->s.ptr = p->s.ptr;
      } else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep) {
      if ((p = morecore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

int main() {
  int const N = 10;
  {
    int *array = malloc_1(sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
      array[i] = i;
      assert(array[i] == i);
    }
    free_1(array);
  }
  {
    int *array = malloc_1(0);
    assert(!array);
  }
  {
    int *array = malloc_1(sizeof(int) * N);
    ((Header *)array - 1)->s.size = 0;
    //    free_1(array); // Error
  }
  {
    char *array1 = malloc_1(sizeof(char) * N);
    char *array2 = malloc_1(sizeof(char) * N);
    ((Header *)array2 - 1)->s.size = N + 2;
    free_1(array1);
    //    free_1(array2); // Error
  }
}
