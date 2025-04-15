#include <stdio.h>

int main() {
    int a, b;
    printf("a b? ");
    scanf("%d %d", &a, &b);

    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
    } else {
        int result = a % b;
        printf("%d\n", result);
    }
}