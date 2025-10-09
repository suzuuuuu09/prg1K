#include <stdio.h>

int main() {
  char inputText[11] = {'\0'};
  int index = 0;

  printf("入力(10文字以内):");
  
  char c;
  while ((c = getchar()) != '\n' && index < 10) {
    inputText[index] = c;
    index++;
  }
  
  index = 0;
  while (inputText[index] != '\0') {
    putchar(inputText[index]);
    index++;
  }
  putchar('\n');
  
  return 0;
}
