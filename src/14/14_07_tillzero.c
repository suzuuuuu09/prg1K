#include <stdio.h>

int main() {
  int wallet = 1000;
  int amount;
  
  while (wallet > 0) {
    printf("amount? ");
    scanf("%d", &amount);
    
    if (amount == 0) {
      printf("取引終了\n");
      break;
    }
    
    wallet -= amount;
    printf("残高: %d\n", wallet);
    
    if (wallet <= 0) {
      break;
    }
  }
  
  return 0;
}