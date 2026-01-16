/* 課題
• 問題８を発展させる
• ファイル読み込み後，ユーザからの入力を任意回数
受け付けて要素を追加/削除できるようにする
• リスト構造の中身を同名ファイルに出力する */
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

    FILE *f = fopen("numlist.txt", "r");
    if(f == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    int number;
    while(fscanf(f, "%d", &number) == 1) {
        add_elem(&root, number);
    }
    fclose(f);

    print_list(root);

    // ファイルに書き込む
    f = fopen("numlist.txt", "w");
    if(f == NULL) {
        printf("ファイルを開けませんでした。\n");
        free_list(root);
        return 1;
    }
    Elem *p = root;
    while (p != NULL) {
        fprintf(f, "%d\n", p->num);
        p = p->next;
    }
    fclose(f);
    free_list(root);

    return 0;
}


