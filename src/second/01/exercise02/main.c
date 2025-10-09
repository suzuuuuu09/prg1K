#include <math.h>
#include <stdio.h>

#define MAX_DEG 360
#define DEG_INCREMENT 10

int main() {
  int deg = 0;

  while (deg <= MAX_DEG) {
    double rad = deg * M_PI / 180;
    printf("θ = %dのとき、sin(θ) = %f\n", deg, sin(rad));

    deg += DEG_INCREMENT;
  }

  return 0;
}

