#include <stdio.h>

int main() {
  int a;

  for(int i = 1; i <= 5; i++) {
    printf("a? ");
    scanf("%d", &a);
    printf("%d: %d\n", i, a);
  }
}
