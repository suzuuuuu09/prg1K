#include <stdio.h>

int main() {
  for (int i = 1; i <= 100; i++) {
    printf("hoge");

    if (i % 2 == 0){
      printf("foo");
    } if (i % 3 == 0){
      printf("bar");
    }

    printf("\n");

  }

  return 0;
}

