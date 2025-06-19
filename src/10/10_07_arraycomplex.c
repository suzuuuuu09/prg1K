#include <stdio.h>
#include <math.h>

int main() {
  int heights[5] = {0};
  int weights[5] = {0};

  int THRESHOLD = 23;
  double standardWeight, bmi;

  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長と体重? ", i + 1);
    scanf("%d %d", &heights[i], &weights[i]);
  }

  printf("--- しきい値を超えた人 ---");

  for (int i = 0; i < 5; i++) {
    standardWeight = (heights[i] - 100) * 0.9;
    bmi = weights[i] / pow(heights[i] / 100.0, 2);
    if(bmi > THRESHOLD) {
      printf("\n%d人目のBMI: %f, 標準体重との差: %f", i + 1, bmi, fabs(weights[i] - standardWeight));
    }
  }
  printf("\n");
}
