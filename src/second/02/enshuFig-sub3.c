#include <stdio.h>

extern int size;

int draw_figure(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      printf(" ");
    }
    printf("*");
    printf("\n");
  }
  return 0;
}
 

