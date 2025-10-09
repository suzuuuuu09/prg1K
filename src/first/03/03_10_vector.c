#include <stdio.h>

int main() {
    int x, y;
    printf("x y? ");
    scanf("(%d, %d)", &x, &y);

    printf("(%d, %d)\n", 2*x, 2*y);
}