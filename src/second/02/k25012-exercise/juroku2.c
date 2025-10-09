#include <stdio.h>

unsigned int number = 0;

int print_hex(unsigned int n) {
  if (n == 0) {
    return 0;
  } else {
    print_hex(n / 16);
    int digit = n % 16;
    if (digit < 10) {
      printf("%d", digit);
    } else {
      printf("%c", 'A' + (digit - 10));
    }
  }
  return 0;
}

int main() {
  printf("number: ");
  scanf("%d", &number);

  print_hex(number);

  return 0;
}


