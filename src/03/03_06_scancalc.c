#include <stdio.h>

int main() {
    int a, b;

    printf("a b? ");
    scanf("%d %d", &a, &b);

    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);

    if (b != 0) {
        printf("%d / %d = %d\n", a, b, a / b);
    } else {
        printf("Division by zero is not allowed.\n");
    }

    return 0;
}