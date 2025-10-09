#include <stdio.h>

int main() {
  double heights[5] = {0};
  double sum = 0;
  
  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長? ", i + 1);
    scanf("%lf", &heights[i]);
    sum += heights[i];
  }
  
  printf("平均身長 = %f\n", sum / 5.0);
  
  return 0;
}