#include <stdio.h>
#include <math.h>

int zanka(int x1, int x2, int n) {
    int xn;
    for (int i = 3; i <= n; i++) {
        xn = x1 + x2;
        x1 = x2;
        x2 = xn;
    }
    return xn;
}

int main() {
    int n = 10;
    int x1 = 1;
    int x2 = 1;
    int xn = zanka(x1, x2, n);

    printf("result = %d\n", xn);

    return 0;
}
