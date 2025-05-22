#include <stdio.h>

int main() {
  int sum = 0;

  while (1) {
    int x;

    printf("x? ");
    scanf("%d", &x);

    if (x == 0) {
      printf("end\n");
      break;
    }

    sum += x;
    printf("sum = %d\n", sum);
  }
}
