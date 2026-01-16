/* 問題６
   • 指定された数字を持つ要素を削除する
   delete_elem(Elem *root, int delnum)を
   実装せよ
   • 削除対象要素のfreeを忘れずに */
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

void delete_elem(Elem **root, int delnum) {
    Elem *current = *root;
    Elem *previous = NULL;

    while (current != NULL) {
        if (current->num == delnum) {
            if (previous == NULL) {
                *root = current->next; // 先頭要素の削除
            } else {
                previous->next = current->next; // 中間または末尾要素の削除
            }
            free(current);
            return; // 削除後に終了
        }
        previous = current;
        current = current->next;
    }
}

int main(void) {
    Elem *root = NULL; // 先頭のポインタを用意

    add_elem(&root, 10);
    add_elem(&root, 7);
    add_elem(&root, 4);
    add_elem(&root, 5);
    add_elem(&root, 200);

    printf("削除前: \n");
    print_list(root);
    printf("\n");

    delete_elem(&root, 10);

    printf("削除後: \n");
    print_list(root);

    free_list(root);

    return 0;
}




