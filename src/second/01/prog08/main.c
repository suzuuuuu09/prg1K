#include <stdio.h>

#define LOOP_COUNT 100
#define FOO_POP 2
#define BAR_POP 3

int main() {
  for (int i = 1; i <= LOOP_COUNT; i++) {
    printf("hoge");

    if (i % FOO_POP == 0){
      printf("foo");
    } if (i % BAR_POP == 0) {
      printf("bar");
    }

    printf("\n");
  }
  printf("\n");

  return 0;
}

