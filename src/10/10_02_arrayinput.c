#include <stdio.h>

int main() {
  int heights[5] = {0};
  double sum = 0;
  double average;

  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長? ", i + 1);
    scanf("%d", &heights[i]);
    sum += heights[i];
  }

  average = sum / 5;
  printf("平均身長 = %f\n", average);
  
  return 0;
}
