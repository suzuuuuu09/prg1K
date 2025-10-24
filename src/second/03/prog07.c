#include <stdio.h>

int main() {
    int a = 10;
    int *px = &a;

    printf("aのアドレス: %p\n", &a);
    printf("pxのアドレス: %p\n", &px);
    
    return 0;
}