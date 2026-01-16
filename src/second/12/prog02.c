/* 問題２
• リストの各要素の内容を標準出力に表示する
関数print_list(Elem *root)を実装する
• root からスタート
• 要素の値を出力する
• nextがNULLになったら終了 */
#include <stdio.h>

typedef struct elem {
  int num;           // データ部
  struct elem *next; // ポインタ部
} Elem;

void print_list(Elem *root) {
  Elem *p = root;
  while (p != NULL) {
    printf("%d\n", p->num);
    p = p->next;
  }
}

int main(void) {
  Elem *root = NULL; // 先頭のポインタを用意

  Elem l1 = {10, root};
  root = &l1;
  Elem l2 = {7, root};
  root = &l2;
  Elem l3 = {4, root};
  root = &l3;

  print_list(root);

  return 0;
}
