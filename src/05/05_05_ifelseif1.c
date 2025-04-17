#include <stdio.h>

int main() {
    int a;
    printf("a? ");
    scanf("%d", &a);

    if (a == 0) {
        printf("aは0です\n");
    }
    else if (a < 0) {
        printf("aは負の値です\n");
    }
    else {
        printf("aは正の値です\n");
    }
}