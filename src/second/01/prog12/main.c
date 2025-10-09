#include <stdio.h>

#define UNDERWEIGHT 18.5
#define NORMAL 25
#define OVERWEIGHT 30
#define CONVERT_CM_TO_M 100.0

int main() {
  int height, weight;
  double bmi = 0;

  printf("身長(cm): ");
  scanf("%d", &height);
  printf("体重(kg): ");
  scanf("%d", &weight);

  double height_meter = height / CONVERT_CM_TO_M;

  bmi = weight / (height_meter * height_meter);

  printf("BMI: %3.2f\n", bmi);

  if (bmi < UNDERWEIGHT) {
    printf("やせ\n");
  } else if (bmi < NORMAL) {
    printf("標準\n");
  } else if (bmi < OVERWEIGHT) {
    printf("肥満\n");
  } else {
    printf("高度肥満\n");
  }

  return 0;
}

