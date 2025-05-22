#include <stdio.h>

int main() {
  int w, h;

  printf("w h? ");
  scanf("%d %d", &w, &h);

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      printf("#");
    }
    printf("\n");
  }
}
