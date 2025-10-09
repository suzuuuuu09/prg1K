#include <stdio.h>

int main() {
  int array[100];
  
  for (int i = 0; i < 100; i++) {
    array[i] = i;
  }
  
  for (int i = 0; i < 100; i++) {
    printf("array[%d]: %d\n", i, array[i]);
  }
  
  return 0;
}
