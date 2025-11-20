/* 問題7 */
/* • ユーザから一つの数字を入力させる */
/* • 負の数が入力されるまで入力を繰り返す */
/* • 全ての入力された値を最後に一度に出力する */
/* • reallocを使うこと */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = NULL;
    int count = 0;
    int num = 0;

    while(1) {
        printf("Enter a number: ");
        scanf("%d", &num);
        if(num >= 0) {
            p = (int *)realloc(p, (count + 1) * sizeof(int));
            p[count] = num;
            count++;
        } else {
            break;
        }
    }
    printf("You entered:\n");
    for(int i = 0; i < count; i++) {
        printf("%d\n", p[i]);
    }

    free(p); /* メモリ開放 */
    return 0;
}
