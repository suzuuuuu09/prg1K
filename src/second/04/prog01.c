#include <stdio.h>

int bad_swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
    
    return 0;
}

int swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    
    return 0;
}

int main() {
    int a = 5;
    int b = 10;
    
    printf("a: %d, b: %d\n", a, b);
    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);

    return 0;
}