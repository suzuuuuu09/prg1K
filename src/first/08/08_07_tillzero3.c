#include <stdio.h>

int main() {
  int wallet = 1000;

  while (wallet > 0) {
    int amount = 0;

    printf("amount? ");
    scanf("%d", &amount);

    if(amount == 0) {
      printf("取引終了\n");
      break;
    }

    wallet -= amount;
    if (amount > 0) {
      printf("残高 = %d\n", wallet);
    }
    else {
      printf("無効です\n");
    }
  }
}
