/* 問題７
• ユーザからのコマンド入力を任意回数受け付けて
その内容をリスト構造に挿入せよ/削除せよ
• ユーザ入力の例
• a 10 ->要素10を新たに挿入
• d 4 ->要素の値が4のものを削除
• p -> 標準出力に現状を表示
• q -> 終了
• 格納したデータを標準出力に表示すること
• メモリの開放を忘れないこと */
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
    char input[32];
    char command;
    int value;

    printf("a: 追加, d: 削除, p: 表示, q: 終了\n");
    while (1) {
        printf("command: ");
        // command入力
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // valueを取得する
        if (sscanf(input, "%c %d", &command, &value) < 1) {
            continue;
        }
        switch(command) {
            case 'a':
                add_elem(&root, value);
                break;
            case 'd':
                delete_elem(&root, value);
                break;
            case 'p':
                print_list(root);
                break;
            case 'q':
                free_list(root);
                return 0;
            default:
                printf("無効なコマンドです\n");
        }

    }
}





