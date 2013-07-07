#include <assert.h>
#include <stdio.h>
#include <time.h>

#define LENGTH 1000000

int binsearch(int x, int const v[], int n) {
  int low = 0;
  int high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int bin_search(int x, int const v[], int n) {
  int low = 0;
  int high = n - 1;
  int mid = (low + high) / 2;
  while (low <= high && v[mid] != x) {
    if (x < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
    mid = (low + high) / 2;
  }
  return low <= high ? mid : -1;
}

int main() {
  int array[LENGTH];
  for (int i = 0; i < LENGTH; ++i) {
    array[i] = i;
  }

  {
    clock_t start = clock();
    int pos = binsearch(LENGTH - 1, array, LENGTH);
    clock_t end = clock();
    printf("Seconds: %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);
    assert(pos == LENGTH - 1);
  }

  {
    clock_t start = clock();
    int pos = bin_search(LENGTH - 1, array, LENGTH);
    clock_t end = clock();
    printf("Seconds: %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);
    assert(pos == LENGTH - 1);
  }
}
