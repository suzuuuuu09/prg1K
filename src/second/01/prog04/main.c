#include <stdio.h>

int main() {
  for (int i = 1; i <= 10; i++) {
    printf("hoge");

    if (i % 3 == 0) {
      printf("\n");
    }
  }
  printf("\n");

  return 0;
}

