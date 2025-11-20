/* 問題3 */
/* • 問題1を，メモリ確保失敗に対応させる */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
     if ((p = (int *)malloc(10*sizeof(int))) == NULL){
        printf("No enough memory.\n");
        exit(1);
    }

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

