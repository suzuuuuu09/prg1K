#include <stdio.h>

int main() {
  int n;
  int sum = 0;
  int i = 1;
  
  printf("n? ");
  scanf("%d", &n);
  
  while (i <= n) {
    sum += i;
    i++;
  }
  
  printf("1から%dまでの和は %d\n", n, sum);
  
  return 0;
}