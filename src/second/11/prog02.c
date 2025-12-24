#include <stdio.h>
#include <math.h>

int zanka(int x, int n) {
    int sum = x;
    for (int i = 1; i < n; i++) {
        sum += 2;
    }
    return sum;
}

int main() {
    int n = 10;
    int x = 1;
    int sum = zanka(x, n);    

    printf("合計: %d\n", sum);
}
