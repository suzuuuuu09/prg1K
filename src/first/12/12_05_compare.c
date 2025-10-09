#include <stdio.h>

int main() {
  int a = 0, b = 0;

  printf("a b? ");
  scanf("%d %d", &a, &b);

  if(a > b) {
    printf("大きい方の値は %d", a);
  } else {
    printf("大きい方の値は %d", b);
  }
  printf("\n");
}
