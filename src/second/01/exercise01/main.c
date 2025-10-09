#include <stdio.h>
#include <math.h>

int main() {
  double radius;

  printf("radius: ");
  scanf("%lf", &radius);

  printf("円周: %lf\n", 2 * M_PI * radius);
  printf("面積: %lf\n", M_PI * radius * radius);

  return 0;
}

