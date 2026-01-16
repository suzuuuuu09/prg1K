/* 問題５
• 先頭要素への追加でなく，小さい順に追加する
ようにadd_elemを変更せよ
• 新しいrootのアドレスをreturnすること */
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
  new_elem->next = NULL;

  if (*root == NULL || (*root)->num >= value) {
    new_elem->next = *root;
    *root = new_elem;
  } else {
    Elem *current = *root;
    while (current->next != NULL && current->next->num < value) {
      current = current->next;
    }
    new_elem->next = current->next;
    current->next = new_elem;
  }
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



