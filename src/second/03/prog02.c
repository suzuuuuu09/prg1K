#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;

    printf("a: %d, b: %d\n", a, b);
    
    int *pa = &a;
    int *pb = &b;

    *pa = 50;
    *pb = 100;
    
    printf("a: %d, b: %d\n", a, b);

    return 0;
}