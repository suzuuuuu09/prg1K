#include <stdio.h>
#include <math.h>

double calcArea (double);/* 半径を引数とし、その円の面積を求める関数 */
double calcCircumference (double);/*  半径を引数とし、その円の周長を求める関数 */

int main() {
  double r = 0.0;

  printf("input r: ");
  scanf("%lf", &r);
  
  printf("%f %f", calcArea(r), calcCircumference(r));
}

double calcArea (double r) {
  return M_PI * pow(r, 2); /* 円の面積を求める */
}

double calcCircumference (double r) {
  return 2 * M_PI * r; /* 円の周長を求める */
}
