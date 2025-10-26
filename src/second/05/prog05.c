#include <stdio.h>
#include <string.h>

/* 問題5 */
/* char a[128]="abc"; */
/* char b[128]; */
/* • 文字列をコピーする関数strcpyを使って */
/* 文字列aをbにコピーせよ */
/* • コピーした結果を表示して確かめよ */

int main() {
  char a[128] = "abc";
  char b[128];

  strcpy(b, a);
  printf("a = \"%s\"\n", a);
  printf("b = \"%s\"\n", b);
}
