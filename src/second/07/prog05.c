/* 問題5 */
/* • ユーザから数字を入力させる */
/* • その数だけ整数値を入力させる */
/* • 整数値を逆順で表示する */
/* • mallocをつかうこと */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *p;

    printf("n: ");
    scanf("%d", &n);

    if((p = (int *)malloc(n * sizeof(int))) == NULL){
        printf("No enough memory.\n");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        printf("p[%d]: ", i);
        scanf("%d", &p[i]);
    }

    printf("逆順表示:\n");
    for(int i = n - 1; i >= 0; i--){
        printf("p[%d] = %d\n", i, p[i]);
    }

    free(p); /* メモリ開放 */
    return 0;
}
