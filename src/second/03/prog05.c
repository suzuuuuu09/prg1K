#include <stdio.h>

int swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    
    return 0;
}

int sort(int *x, int *y) {
    if (*x > *y) {
        swap(x, y);
    }

    return 0;
}

int main() {
    int a = 20;
    int b = 10;

    printf("a: %d, b: %d\n", a, b);

    sort(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}