#include <stdio.h>

int main() {
  int heightsCm[5] = {0};
  double heightsMeter[5] = {0.0};

  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長(cm)? ", i + 1);
    scanf("%d", &heightsCm[i]);
    heightsMeter[i] = heightsCm[i] / 100.0; // cm to m
  }

  printf("--- Convert Meter ---\n");

  for (int i = 0; i < 5; i++) {
    printf("%d人目の身長(m): %f m", i + 1, heightsMeter[i]);
    printf("\n");
  }

  return 0;
}
