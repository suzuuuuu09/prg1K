#include <stdio.h>

int main() {
  char inputText[21] = {'\0'};
  int count = 0;

  printf("input(20文字以下):");
  scanf("%20s", inputText);

  for (int i = 0; inputText[i] != '\0'; i++) {
    if (inputText[i] == 'a' || inputText[i] == 'A') {
      count++;
    }
  }

  printf("aの数: %d\n", count);

  return 0;
}
