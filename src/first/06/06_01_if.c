#include <stdio.h>

int main() {
    int a;

    printf("a? ");
    scanf("%d", &a);

    if (a == 0)
        printf("aは0です\n");
    else if(a > 0)
        printf("aは正の数です\n");
    else
        printf("aは負の数です\n");
    return 0;
}