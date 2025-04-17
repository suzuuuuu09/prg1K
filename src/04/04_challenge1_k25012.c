#include <stdio.h>

int main() {
    int x;
    printf("x? ");
    scanf("%d", &x);

    int digit_1 = x % 10; // 1の位
    int digit_10 = (x / 10) % 10; // 10の位
    int digit_100 = (x / 100) % 10; // 100の位

    printf("reverse x = %d%d%d\n", digit_1, digit_10, digit_100);
}