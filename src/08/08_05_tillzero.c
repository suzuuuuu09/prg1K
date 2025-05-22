#include <stdio.h>

int main() {
  int wallet = 1000;

  while (wallet > 0) {
    int amount = 0;

    printf("amount? ");
    scanf("%d", &amount);

    wallet -= amount;
    printf("残高 = %d\n", wallet);
  }
}
