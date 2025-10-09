#include <stdio.h>

int main() {
    int a, b;
    printf("a? ");
    scanf("%d", &a);
    printf("b? ");
    scanf("%d", &b);
    
    if (a >= b) {
        printf("aはb以上です\n");
    }
    else {
        printf("aはb未満です\n");
    }

    return 0;
}