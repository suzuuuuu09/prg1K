#include <stdio.h>

int main() {
  int x, y, z;
  
  printf("x y z? ");
  
  int temp;
  if (x > y) {
    temp = x;
    x = y;
    y = temp;
  }
  if (y > z) {
    temp = y;
    y = z;
    z = temp;
  }
  if (x > y) {
    temp = x;
    x = y;
    y = temp;
  }
  
  printf("%d %d %d\n", x, y, z);
}
