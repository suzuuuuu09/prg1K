#include <stdio.h>
#include <math.h>

int main() {
  double x;
  int selected;

  printf("x? ");
  scanf("%lf", &x);

  printf("--- menu ---\n");
  printf("1: 絶対値, 2: 2乗, 3: 3乗\n");
  printf("menu no? ");
  scanf("%d", &selected);

  switch(selected) {
    case 1:
      printf("|%lf| = %f\n", x, fabs(x));
      break;
    case 2:
      printf("%lf ^ 2 = %lf\n", x, pow(x, 2));
      break;
    case 3:
      printf("%lf ^ 3 = %lf\n", x, pow(x, 3));
      break;
  }
}
