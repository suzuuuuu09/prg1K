#include <stdio.h>

int main() {
  int bank = 1000;
  int wallet = 1000;

  while (1) {
    int amount = 0;

    printf("amount? ");
    scanf("%d", &amount);

    if (amount == 0) {
      break;
    }
    else if (amount > 0) {
      bank -= amount;
      wallet += amount;
    }
    else if (amount < 0) {
      bank -= amount;
      wallet += amount;
    }

    printf("銀行: %d 財布: %d\n", bank, wallet);

    if (bank <= 0 || wallet <= 0) {
      break;
    }
  }

  return 0;
}
