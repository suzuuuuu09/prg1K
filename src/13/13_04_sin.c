#include <math.h>
#include <stdio.h>

int main() {
  double theta = 0.0;
  double rad = 0.0;

  printf("input: ");
  scanf("%lf", &theta);

  rad = theta * M_PI / 180.0;
  printf("sin (%f) = %f\n", theta, sin(rad));
}
