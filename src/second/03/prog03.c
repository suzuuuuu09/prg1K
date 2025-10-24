#include <stdio.h>

void getSumDiff(int num1, int num2, int *sum, int *diff) {
    *sum = num1 + num2;
    *diff = num1 - num2;
}

int main(void) {
    int num1 = 10, num2 = 5, sum = 0, diff = 0;

    getSumDiff(num1, num2, &sum, &diff);
    printf("%d, %d\n", sum, diff);

    return 0;
}