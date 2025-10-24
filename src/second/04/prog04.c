#include <stdio.h>

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    int *pa = a; // 配列の先頭要素のポインター

    for(int i = 0; i < 5; i++) {
        printf("a[%d]のポインター: %p, 値: %d\n", i, (pa + i), *(pa + i));
    }

    return 0;
}