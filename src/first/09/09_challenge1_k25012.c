#include <stdio.h>

int main() {
  char ch;
  int isMinus = 0;
  int answer = 0;
  int inputNumber = 0;

  printf("equation? ");
  while ((ch = getchar()) != '=') {
    switch (ch) {
      case '-':
        isMinus = 1;
        break;
      case '+':
        isMinus = 0;
        break;
      case ' ':
        if (isMinus) {
          answer -= inputNumber;
        } else {
          answer += inputNumber;
        }
        inputNumber = 0;
        break;
      default:
        // 数字
        if (ch >= '0' && ch <= '9') {
          inputNumber = ch - '0';
        }
        break;
    }
  }
  
  printf("answer: %d\n", answer);
  return 0;
}
