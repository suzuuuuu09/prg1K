#include <stdio.h>

int main() {
  int x, y;

  printf("x y? ");
  scanf("%d %d", &x, &y);
  if (y < x) {
    int temp = x;
    x = y;
    y = temp;
  }
  printf("%d %d\n", x, y);
}
