#include <stdio.h>

int main() {
  int heights[5] = {0};
  int max, min;

  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長? ", i + 1);
    scanf("%d", &heights[i]);
  }

  max = heights[0];
  min = heights[0];

  for (int i = 1; i < 5; i++) {
    if (heights[i] > max) {
      max = heights[i];
    }
    if (heights[i] < min) {
      min = heights[i];
    }
  }

  printf("最小身長は %d\n", min);
  printf("最大身長は %d\n", max);

  return 0;
}