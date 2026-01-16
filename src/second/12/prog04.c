/* 問題４
• 全リスト要素のメモリを開放する
free_list(Elem *root)を実装せよ */
#include <stdio.h>
#include <stdlib.h>

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

void add_elem(Elem **root, int value) {
  Elem *new_elem = (Elem *)malloc(sizeof(Elem));
  new_elem->num = value;
  new_elem->next = *root;
  *root = new_elem;
}

void free_list(Elem *root) {
  Elem *p = root;
  while (p != NULL) {
    Elem *next = p->next;
    free(p);
    p = next;
  }
}

int main(void) {
  Elem *root = NULL; // 先頭のポインタを用意

  add_elem(&root, 10);
  add_elem(&root, 7);
  add_elem(&root, 4);

  print_list(root);

  free_list(root);

  return 0;
}


