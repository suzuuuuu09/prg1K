#include <stdio.h>

void multiply_by_ten(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        *(arr + i) *= 10;
    }
}

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int b[4] = {3, 4, 5, 6};

    multiply_by_ten(a, 5);
    multiply_by_ten(b, 4);
    
    for(int i = 0; i < 5; i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }

    for(int i = 0; i < 4; i++) {
        printf("b[%d]: %d\n", i, b[i]);
    }

    return 0;
}
