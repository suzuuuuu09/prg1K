#include <stdio.h>

int main() {
    int a = 3;
    int b = 4;
    int c = 2;
    int d = 8;

    int result = a + b * c / d;
    
    printf("%d + %d * %d / %d = %d\n", a, b, c, d, result);
}