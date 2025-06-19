#include <stdio.h>

int main() {
  int evenNumbers[5] = {2, 4, 6, 8, 10};
  int sum = 0;

  for (int i = 0; i < 5; i++) {
    sum += evenNumbers[i];
  }

  printf("合計 = %d\n", sum);
}
