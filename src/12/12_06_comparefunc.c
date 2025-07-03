#include <stdio.h>

int maxOf(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int main() {
  int a = 0, b = 0;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  printf("大きい方の値は %d\n", maxOf(a, b));

  return 0;
}

