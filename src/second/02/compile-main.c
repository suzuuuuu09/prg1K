#include <stdio.h>

// プロトタイプ宣言
// 「extern」とは「別ファイルに定義本体があるよ」という意味
extern int sub(int);

int b;

int main() {
    b = 10;
    printf("%d\n", sub(b));
}
