#include <stdio.h>

int main() {
  int n, x;
  int count = 0;

  printf("n x? ");
  scanf("%d %d", &n, &x);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int k = x - i - j;
      if (k > 0 && k <= n) {
        printf("%d%d%d\n", i, j, k);
        count++;
      }
    }
  }

  printf("組み合わせの数: %d\n", count);
}
