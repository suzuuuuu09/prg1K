#include <stdio.h>

int main() {
  char inputText[11] = {'\0'};

  printf("入力(10文字以内):");
  scanf("%10s", inputText);
  
  printf("%s\n", inputText);
}
