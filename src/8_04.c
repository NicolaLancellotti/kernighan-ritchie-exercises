#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iob_1 {
  int cnt;
  char *ptr;
  char *base;
  int flag;
  int fd;
} FILE_1;
extern FILE_1 _iob_1[OPEN_MAX];

#define stdin_1 (&_iob_1[0])
#define stdout_1 (&_iob_1[1])
#define stderr_1 (&_iob_1[2])

enum flags {
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020,
  _APPEND = 040
};

FILE_1 _iob_1[OPEN_MAX] = {{0, (char *)0, (char *)0, _READ, 0},
                           {0, (char *)0, (char *)0, _WRITE, 1},
                           {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int _fillbuf_1(FILE_1 *);
int _flushbuf_1(int, FILE_1 *);

#define feof_1(p) (((p)->flag & _EOF) != 0)
#define ferror_1(p) (((p)->flag & _ERR) != 0)
#define fileno_1(p) ((p)->fd)

#define getc_1(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf_1(p))
#define putc_1(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf_1((x), p))

#define getchar_1() getc_1(stdin_1)
#define putchar_1(x) putc_1(x, stdout_1)

#define PERMS 0666

FILE_1 *fopen_1(char const *name, char const *mode) {
  int fd;
  FILE_1 *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    return NULL;
  }
  for (fp = _iob_1; fp < _iob_1 + OPEN_MAX; ++fp) {
    if ((fp->flag & (_READ | _WRITE)) == 0) {
      break;
    }
  }
  if (fp >= _iob_1 + OPEN_MAX) {
    return NULL;
  }

  if (*mode == 'w') {
    fd = creat(name, PERMS);
  } else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1) {
      fd = creat(name, PERMS);
    }
    lseek(fd, 0L, 2);
  } else {
    fd = open(name, O_RDONLY, 0);
  }
  if (fd == -1) {
    return NULL;
  }
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  if (*mode == 'a') {
    fp->flag |= _APPEND;
  }
  return fp;
}

int _fillbuf_1(FILE_1 *fp) {
  int bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
    fp->cnt = 0;
    return EOF;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if (fp->base == NULL) {
    if ((fp->base = (char *)malloc(bufsize)) == NULL) {
      fp->cnt = 0;
      return EOF;
    }
  }
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1) {
      fp->flag |= _EOF;
    } else {
      fp->flag |= _ERR;
    }
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

int fflush_1(FILE_1 *fp) {
  if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE || !fp->base) {
    return EOF;
  }
  int values = BUFSIZE - fp->cnt;
  fp->ptr = fp->base;
  if (write(fp->fd, fp->ptr, values) != values) {
    fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  fp->cnt = BUFSIZE;
  return 0;
}

int _flushbuf_1(int c, FILE_1 *fp) {
  if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
    fp->cnt = 0;
    return EOF;
  }

  if (fp->flag & _UNBUF) {
    fp->cnt = 0;
    if (write(fp->fd, &c, 1) != 1) {
      fp->flag |= _ERR;
      return EOF;
    }
    return c;
  }

  int bufsize = BUFSIZE;
  if (fp->base == NULL) {
    if ((fp->ptr = fp->base = (char *)malloc(bufsize)) == NULL) {
      fp->cnt = 0;
      return EOF;
    }
    fp->cnt = bufsize - 1;
    *(fp)->ptr++ = c;
    return c;
  }

  fp->ptr = fp->base;
  if (write(fp->fd, fp->ptr, bufsize) != bufsize) {
    fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  fp->cnt = bufsize;
  return c;
}

int fclose_1(FILE_1 *fp) {
  fflush_1(fp);
  int fd = fp->fd;
  free(fp->base);
  fp->cnt = fp->flag = 0;
  fp->base = fp->ptr = NULL;
  fp->fd = -1;
  return close(fd);
}

#define SEEK_SET_1 0
#define SEEK_CUR_1 1
#define SEEK_END_1 2
int fseek_1(FILE_1 *fp, long offset, int origin) {
  if (fp->flag & _APPEND) {
    // On the append file access modes, data is written to the end of the file
    // regardless of the current position of the file position indicator.
    return 0;
  }
  if (fp->flag & _ERR) {
    return -1;
  }
  if (fp->flag & _WRITE) {
    fflush_1(fp);
  }

  if (fp->flag & _READ) {
    if (origin == SEEK_CUR_1) {
      offset = offset - fp->cnt;
    }
    fp->ptr = fp->base;
    fp->cnt = 0;
    fp->flag &= ~_EOF;
  }

  int result = lseek(fp->fd, offset, origin);
  return result == -1 ? -1 : 0;
}

#include <assert.h>
#include <stdio.h>

void test_1(char const *file) {
  {
    FILE_1 *fp = fopen_1(file, "w");
    putc_1('0', fp);
    putc_1('1', fp);
    putc_1('2', fp);

    assert(!fseek_1(fp, -1, SEEK_CUR_1));
    putc_1('C', fp);
    assert(!fseek_1(fp, 0, SEEK_SET_1));
    putc_1('A', fp);
    assert(!fseek_1(fp, -2, SEEK_END_1));
    putc_1('B', fp);
    fclose_1(fp);
  }
  {
    FILE_1 *fp = fopen_1(file, "r");
    assert(getc_1(fp) == 'A');
    assert(getc_1(fp) == 'B');
    assert(getc_1(fp) == 'C');
    assert(getc_1(fp) == EOF);

    assert(!fseek_1(fp, -2, SEEK_END_1));
    assert(getc_1(fp) == 'B');
    assert(!fseek_1(fp, -1, SEEK_CUR_1));
    assert(getc_1(fp) == 'B');
    assert(!fseek_1(fp, 0, SEEK_SET_1));
    assert(getc_1(fp) == 'A');
    fclose_1(fp);
  }
  {
    FILE_1 *fp = fopen_1(file, "a");
    putc_1('0', fp);
    putc_1('1', fp);
    putc_1('2', fp);
    assert(!fseek_1(fp, 0, SEEK_SET_1));
    putc_1('D', fp);
    assert(!fseek_1(fp, -2, SEEK_END_1));
    putc_1('E', fp);
    assert(!fseek_1(fp, -1, SEEK_CUR_1));
    putc_1('F', fp);
    fclose_1(fp);

    fp = fopen_1(file, "r");
    assert(getc_1(fp) == 'A');
    assert(getc_1(fp) == 'B');
    assert(getc_1(fp) == 'C');
    assert(getc_1(fp) == '0');
    assert(getc_1(fp) == '1');
    assert(getc_1(fp) == '2');
    assert(getc_1(fp) == 'D');
    assert(getc_1(fp) == 'E');
    assert(getc_1(fp) == 'F');
    assert(getc_1(fp) == EOF);
    fclose_1(fp);
  }
}

void test(char const *file) {
  {
    FILE *fp = fopen(file, "w");
    putc('0', fp);
    putc('1', fp);
    putc('2', fp);

    assert(!fseek(fp, -1, SEEK_CUR));
    putc('C', fp);
    assert(!fseek(fp, 0, SEEK_SET));
    putc('A', fp);
    assert(!fseek(fp, -2, SEEK_END));
    putc('B', fp);
    fclose(fp);
  }
  {
    FILE *fp = fopen(file, "r");
    assert(getc(fp) == 'A');
    assert(getc(fp) == 'B');
    assert(getc(fp) == 'C');
    assert(getc(fp) == EOF);

    assert(!fseek(fp, -2, SEEK_END));
    assert(getc(fp) == 'B');
    assert(!fseek(fp, -1, SEEK_CUR));
    assert(getc(fp) == 'B');
    assert(!fseek(fp, 0, SEEK_SET));
    assert(getc(fp) == 'A');
    fclose(fp);
  }
  {
    FILE *fp = fopen(file, "a");
    putc('0', fp);
    putc('1', fp);
    putc('2', fp);
    assert(!fseek(fp, 0, SEEK_SET));
    putc('D', fp);
    assert(!fseek(fp, -2, SEEK_END));
    putc('E', fp);
    assert(!fseek(fp, -1, SEEK_CUR));
    putc('F', fp);
    fclose(fp);

    fp = fopen(file, "r");
    assert(getc(fp) == 'A');
    assert(getc(fp) == 'B');
    assert(getc(fp) == 'C');
    assert(getc(fp) == '0');
    assert(getc(fp) == '1');
    assert(getc(fp) == '2');
    assert(getc(fp) == 'D');
    assert(getc(fp) == 'E');
    assert(getc(fp) == 'F');
    assert(getc(fp) == EOF);
    fclose(fp);
  }
}

int main(int argc, char const *argv[]) {
  char const *file = argv[1];
  test_1(file);
  test(file);
}
