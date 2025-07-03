#include <stdio.h>
#include <math.h>

double deg2Rad(double);

int main() {
  double theta = 0.0;
  double rad = 0.0;

  printf("input: ");
  scanf("%lf", &theta);

  rad = deg2Rad(theta);
  printf("sin (%f) = %f\n", theta, sin(rad));

  return 0;

}

double deg2Rad(double deg) {
  return deg * 3.14159265358979323846 / 180.0;
}
