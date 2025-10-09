#include <stdio.h>

int main() {
  int numbers[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int sum = 0;
  
  for (int i = 0; i < 10; i++) {
    sum += numbers[i];
  }
  
  printf("合計 = %d\n", sum);
  
  return 0;
}