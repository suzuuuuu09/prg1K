#include <stdio.h>

int main() {
  int primeNumbers[100] = {0};
  int isPrime = 0;
  int count = 0;

  for (int i = 2; i < 100; i++) {
    for(int j = 0; j < 100; j++) {
      if (primeNumbers[j] == 0) {
        isPrime = 1;
        for (int k = 2; k * k <= i; k++) {
          if (i % k == 0) {
            isPrime = 0;
            break;
          }
        }
        if (isPrime) {
          primeNumbers[j] = i;
          count++;
          break;
        }
      }
    }

  }

  for (int i = 0; i < count; i++) {
    printf("%d, ", primeNumbers[i]);
  }

  printf("\n");
}
