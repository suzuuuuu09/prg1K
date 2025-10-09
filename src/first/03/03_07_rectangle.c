#include <stdio.h>

int main() {
    int a, b, perimeter, area;

    printf("a b? ");
    scanf("%d %d", &a, &b);

    perimeter = 2 * (a + b);
    area = a * b;

    printf("Perimeter = %d\n", perimeter);
    printf("Area = %d\n", area);
}