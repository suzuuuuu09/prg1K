#include <stdio.h>

int main() {
  char c;
  
  printf("c? ");
  c = getchar();
  
  switch (c) {
    case 'L':
      printf("Left\n");
      break;
    case 'R':
      printf("Right\n");
      break;
    default:
      printf("nop\n");
      break;
  }
  
  return 0;
}