#include <stdio.h>

#define LOOP_COUNT 10
#define BREAK_NUMBER 3

int main() {
  for (int i = 1; i <= LOOP_COUNT; i++) {
    printf("hoge");
    if (i % BREAK_NUMBER == 0) {
      printf("\n");
    }
  }
  printf("\n");

  return 0;
}

