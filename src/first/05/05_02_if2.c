#include <stdio.h>

int main() {
    int a, b;
    printf("a? ");
    scanf("%d", &a);
    printf("b? ");
    scanf("%d", &b);

    if (a == b) {
        printf("aとbの値は等しいです\n");
    }
    printf("計算終了\n");
}