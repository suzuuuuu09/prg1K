#include <stdio.h>

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a; // 配列の先頭要素のポインター

    for(int i = 0; i < 5; i++) {
        *(p + i) *= 10;
    }
    
    for(int i = 0; i < 5; i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }

    return 0;
}
