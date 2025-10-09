#include <stdio.h>

int main(void) {
    int a;

    printf("a? ");
    scanf("%d", &a);

    if (a > 0) {
        printf("aは正の値です\n");
    }

    printf("計算終了\n");

    return 0;
}