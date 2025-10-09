#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 3
#define MAX 5

int rand_num(int min, int max) {
  return rand() % (max - min + 1) + min;
}

int main() {
  srand(time(NULL));
  int n = rand_num(MIN, MAX);

  printf("%d\n", n);

  return 0;
}

