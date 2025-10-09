#include <stdio.h>

int main() {
  int sum = 0;
  int x = 1;

  while (x != 0) {
    printf("x? ");
    scanf("%d", &x);
    sum += x;
    printf("sum = %d\n", sum);
  }

  printf("end\n");

  return 0;
}
