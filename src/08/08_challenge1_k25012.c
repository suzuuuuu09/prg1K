#include <stdio.h>

int main() {
  int input=0;

  printf("input? ");
  scanf("%d", &input);
  int num = input;
  int factor = 2;
  
  while (num > 1) {
    if (num % factor == 0) {
      printf("%d", factor);
      num /= factor;
      if (num > 1) {
        printf(", ");
      }
    } else {
      factor++;
    }
  }
  printf("\n");

  return 0;
}
