#include <stdio.h>

int main() {
    double a, b;

    printf("a b? ");
    if (scanf("%lf %lf", &a, &b) == 2) {
        printf("a = %f, b = %f\n", a, b);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}