#include <stdio.h>
#include <math.h>

int sigma(int a, int n) {
    int sum = 0;
    for (int k = 0; k <= n; k++) {
        sum += pow(a, n - k);
    }
    return sum;
}

int main() {
    int n = 10;
    int a = 4;
    int sum = sigma(a, n);

    printf("Sum: %d\n", sum);

    return 0;
}
