
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_num(int min, int max) {
  return rand() % (max - min + 1) + min;
}

int main() {
  srand(time(NULL));
  int n, min, max;

  printf("min: ");
  scanf("%d", &min);
  printf("max: ");
  scanf("%d", &max);

  if(min > max) {
    printf("minはmaxよりも小さい値にしてね♡\n");
    return 0;
  }

  n = rand_num(min, max);
  printf("%d\n", n);

  return 0;
}


