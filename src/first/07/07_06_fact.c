#include <stdio.h>

int main() {
  int x, n;
  int result = 1;

  printf("x n? ");
  scanf("%d %d", &x, &n);

  for (int i = 1; i <= n; i++) {
    result *= x;
  }

  printf("%d\n", result);
  return 0;
}