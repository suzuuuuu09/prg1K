#include <stdio.h>

int main() {
  char array[] = "abcde";

  printf("一文字ずつ印字: ");

  for (int i = 0; array[i] != '\0'; i++) {
    printf("%c", array[i]);
  }

  printf("\n");

  return 0;
}
