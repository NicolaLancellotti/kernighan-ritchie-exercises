#define Exercise

#ifdef Exercise
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
  int fd;
  int read : 1;
  int write : 1;
  int unbuf : 1;
  int eof : 1;
  int err : 1;
} FILE_1;
extern FILE_1 _iob_1[OPEN_MAX];

#define stdin_1 (&_iob_1[0])
#define stdout_1 (&_iob_1[1])
#define stderr_1 (&_iob_1[2])

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
    if (!fp->read && !fp->write) {
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
  fp->read = *mode == 'r';
  fp->write = !fp->read;
  return fp;
}

int _fillbuf_1(FILE_1 *fp) {
  int bufsize;
  if (!fp->read || fp->eof || fp->err) {
    return EOF;
  }
  bufsize = fp->unbuf ? 1 : BUFSIZE;
  if (fp->base == NULL) {
    if ((fp->base = (char *)malloc(bufsize)) == NULL) {
      return EOF;
    }
  }
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1) {
      fp->eof = 1;
    } else {
      fp->err = 1;
    }
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

FILE_1 _iob_1[OPEN_MAX] = {{0, (char *)0, (char *)0, 0, 1, 0, 0, 0, 0},
                           {0, (char *)0, (char *)0, 1, 0, 1, 0, 0, 0},
                           {0, (char *)0, (char *)0, 2, 0, 1, 1, 0, 0}};

#else

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

enum flags { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

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
  return fp;
}

int _fillbuf_1(FILE_1 *fp) {
  int bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
    return EOF;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
  if (fp->base == NULL) {
    if ((fp->base = (char *)malloc(bufsize)) == NULL) {
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

FILE_1 _iob_1[OPEN_MAX] = {{0, (char *)0, (char *)0, _READ, 0},
                           {0, (char *)0, (char *)0, _WRITE, 1},
                           {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

#endif

#include <stdio.h>

int main(int argc, char const *argv[]) {
  FILE_1 *fp = fopen_1(argv[1], "r"); /**/
  for (int c; (c = getc_1(fp)) != EOF;) {
    printf("%c", c);
  }
}