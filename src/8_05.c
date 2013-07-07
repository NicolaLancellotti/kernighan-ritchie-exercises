#ifdef __APPLE__

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>

#define MAX_PATH 1024

void dirwalk(char const *dir, void (*fcn)(char const *)) {
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
      fprintf(stderr, "dirwal: name %s/%s too long\n", dir, dp->d_name);
    } else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}

void fsize(char const *name) {
  struct stat stbuf;
  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    dirwalk(name, fsize);
  }

  printf("%8lldB\t%d uid\t%d gid\t%s\n", stbuf.st_size, stbuf.st_uid,
         stbuf.st_gid, name);
}

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    fsize(".");
  } else {
    while (--argc > 0) {
      fsize(*++argv);
    }
  }
}

#endif
