#include <stdio.h>

int main() {
    int x;
    
    printf("x? ");
    scanf("%d", &x);

    printf("x = %d, 2x = %d, 3x = %d\n", x, 2*x, 3*x);
}