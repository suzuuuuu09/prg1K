#include <stdio.h>

int swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    
    return 0;
}

int main() {
    int a = 10;
    int b = 20;

    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}