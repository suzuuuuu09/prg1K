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

int sort_three_value(int *x, int *y, int *z) {
    sort(x, y);
    sort(y, z);
    sort(x, y);

    return 0;
}

int main() {
    int a = 20;
    int b = 30;
    int c = 10;
    
    printf("a: %d, b: %d, c: %d\n", a, b, c);
    
    sort_three_value(&a, &b, &c);
    printf("a: %d, b: %d, c: %d\n", a, b, c);
    
    return 0;
}