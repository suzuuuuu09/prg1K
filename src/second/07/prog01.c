/* 問題1 */
/* • intのポインタ pを用意する */
/* • 動的にint４つ分のメモリ領域を確保する */
/* • ４つ分の領域にそれぞれ数字を入れる */
/* • 表示する */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
    p = (int*)malloc(4 * sizeof(int));
    p[0] = 10;
    p[1] = 20;
    p[2] = 30;
    p[3] = 40;

    for (int i = 0; i < 4; i++) {
        printf("p[%d] = %d\n", i, p[i]);
    }

    free(p); /* メモリ開放 */
    return 0;
}
