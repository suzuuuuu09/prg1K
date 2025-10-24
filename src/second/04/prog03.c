#include <stdio.h>

int main() {
    double a[3] = {1.1, 2.2, 3.3};
    
    for (int i = 0; i < 3; i++) {
        printf("a[%d]のポインター: %p\n", i, &a[i]);
    }
    
    return 0;
}