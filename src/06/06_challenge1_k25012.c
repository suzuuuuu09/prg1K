#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    bool isPrimeNumber = false;

    printf("n? ");
    scanf("%d", &n);

    /* 素数の判別をする */
    if (n <= 1) {
        isPrimeNumber = false;
    } else {
        isPrimeNumber = true;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                isPrimeNumber = false;
                break;
            }
        }
    }

    if(isPrimeNumber) {
        printf("素数です\n");
    } else {
        printf("素数ではありません\n");
    }
}