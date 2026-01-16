/* 問題１
• リスト構造実装のために，前頁のプログラムを
用意せよ */
#include <stdio.h>

typedef struct elem {
  int num; // データ部
  struct elem *next; // ポインタ部
} Elem;

int main(void) {
  Elem *root = NULL;

  return 0;
}
