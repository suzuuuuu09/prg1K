#include <stdio.h>

extern int size;

int draw_figure(int n) {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      printf("*");
    }
    printf("\n");
  }
  return 0;
}
 

