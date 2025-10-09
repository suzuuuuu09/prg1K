#include <stdio.h>

int main() {
  int heights[5] = {0};
  int THRESHOLD = 170;

  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長? ", i + 1);
    scanf("%d", &heights[i]);
  }

  printf("--- しきい値を超えた人 ---\n");

  for (int i = 0; i < 5; i++) {
    if (heights[i] >= THRESHOLD) {
      printf("%d人目の身長 %d\n", i + 1, heights[i]);
    }
  }

  return 0;
}
