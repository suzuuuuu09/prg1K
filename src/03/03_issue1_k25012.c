#include <stdio.h>

int main() {
    int a = 6;
    int b = 4;
    int c = 2;
    int d = a - (b / c);

    printf("%d - (%d / %d) = %d\n", a, b, c, d);
}