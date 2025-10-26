#include <stdio.h>

/* 問題3 */
/* • 前頁のマジックナンバー "3" を使わない方式に 書き換えなさい */
/* • 配列の要素数を得る方法は？ */

int main(void) {
  int i;
  char a[][5] = {"LISP", "C", "Ada"};
  char *p[] = {"PAUL", "X", "MAC"};

  size_t size_a = sizeof(a) / sizeof(a[0]);
  for (i = 0; i < size_a; i++) {
    printf("a[%d] = \"%s\"\n", i, a[i]);
  }

  size_t size_p = sizeof(p) / sizeof(p[0]);
  for (i = 0; i < size_p; i++) {
    printf("p[%d] = \"%s\"\n", i, p[i]);
  }

  return 0;
}
