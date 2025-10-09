#include <stdio.h>

unsigned int number = 0;

// シフトを使って2進数を表示
void printbin(unsigned int x) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
}

int main() {
  printf("number: ");
  scanf("%d", &number);

  printbin(number);

  return 0;
}
