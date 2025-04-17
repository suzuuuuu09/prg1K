#include <stdio.h>

int main() {
    int x;
    printf("x? ");
    scanf("%d", &x);

    if(x % 2 == 0) {
        printf("even\n");
    }
    else {
        printf("odd\n");
    }
}