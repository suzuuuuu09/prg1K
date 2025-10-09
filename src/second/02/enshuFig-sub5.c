#include <stdio.h>

extern int size;

int draw_figure(int n) {
  for (int i = n; i > 0; i--) {
    for (int j = 1; j < i; j++) {
      printf(" ");
    }
    printf("*");
    printf("\n");
  }
  return 0;
}
 


