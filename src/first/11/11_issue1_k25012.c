#include <stdio.h>

int main() {
  char inputText[21] = {'\0'};
  int isPalindrome = 1;

  printf("input(20文字以下):");
  scanf("%20s", inputText);
  
  int length = 0;
  while (inputText[length] != '\0') {
    length++;
  }

  for(int i = 0; i < length / 2; i++) {
    if(inputText[i] != inputText[length - 1 - i]) {
      isPalindrome = 0;
    }
  }
  
  if(isPalindrome) {
    printf("回文OK\n");
  } else {
    printf("回文NG\n");
  }
}
