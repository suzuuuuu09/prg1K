#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    int isPrimeNumber = 0;

    printf("n? ");
    scanf("%d", &n);

    /* 素数の判別をする */
    if (n <= 1) {
        isPrimeNumber = 0;
    } else {
        for (int i = 2; i * i <= n && isPrimeNumber == 0; i++) {
            if (n % i == 0) {
                isPrimeNumber = 1;
            }
        }
    }

    if(isPrimeNumber == 1) {
        printf("素数です\n");
    } else {
        printf("素数ではありません\n");
    }
}