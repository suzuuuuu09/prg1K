#include <stdio.h>

int main() {
  char inputText[6] = {'\0'};

  printf("入力(5文字以内):");
  scanf("%5s", inputText);

  for (int i = 5; i >= 0; i--) {
    printf("%c", inputText[i]);
  }
  printf("\n");

  return 0;
}
