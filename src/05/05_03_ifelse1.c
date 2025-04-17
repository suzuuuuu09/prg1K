#include <stdio.h>

int main() {
    int a;
    printf("a? ");
    scanf("%d", &a);

    if (a >= 0) {
        printf("aは正の値もしくは0です\n");
    }
    else {
        printf("aは負の値です\n");
    }
}