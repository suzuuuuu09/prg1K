#include <stdio.h>

/* 問題4 */
/* • char *str="abcd"; */
/* • strの文字を一文字ずつ縦に並べて出力せよ */
/* a */
/* b */
/* c */
/* d */

int main() {
  char *str = "abcd";

  for (int i = 0; str[i] != '\0'; i++) {
    printf("%c\n", str[i]);
  }
}
