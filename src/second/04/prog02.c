#include <stdio.h>

int main() {
    int a[3] = {10, 20, 30};

    for (int i = 0; i < 3; i++) {
        printf("a[%d]のポインター: %p\n", i, &a[i]);
    }
    
    return 0;
}