#include <stdio.h>

int main() {
  char array[11] = {"\0"};
  printf("入力(10文字以内): ");
  scanf("%10s", array);
  printf("%s\n", array);
}
