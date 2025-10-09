#include <stdio.h>

int main() {
  int h1, h2, h3;
  double average;

  printf("1人目の身長は? ");
  scanf("%d", &h1);
  printf("2人目の身長は? ");
  scanf("%d", &h2);
  printf("3人目の身長は? ");
  scanf("%d", &h3);
  
  average = (h1 + h2 + h3) / 3.0;
  printf("平均身長は %f\n", average);
  
  return 0;
}
