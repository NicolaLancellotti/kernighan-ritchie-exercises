#include <string.h>

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
  Header *p;
  Header *bp = (Header *)ap - 1;
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break;
    }
  }

  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if (p + p->s.size == bp) {
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

void bfree(char *p, unsigned n) {
  uintptr_t mod = (uintptr_t)p % _Alignof(Header);
  if (mod != 0) {
    uintptr_t v = _Alignof(Header) - mod;
    p += v;
    n -= v;
  }

  if (n < sizeof(Header) * 2) {
    return;
  }

  Header *bp = (Header *)p;
  bp->s.size = n / sizeof(Header);

  if (!freep) {
    base.s.ptr = freep = &base;
    base.s.size = 0;
  }
  free_1(bp + 1);
}

#define N 50
static char s[N];

int main() { bfree(&s[8], N); }
