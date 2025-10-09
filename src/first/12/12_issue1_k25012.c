#include <stdio.h>

int factOf(int n) {
  int result = 1;
  for (int i = 2; i <= n; i++) {
    result *= i;
  }

  return result;
}

int main() {
  int n = 0;

  printf("n? ");
  scanf("%d", &n);

  printf("%dの階乗は %d\n", n, factOf(n));

  return 0;
}

