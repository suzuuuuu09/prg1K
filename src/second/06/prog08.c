#include <stdio.h>

int main() {
    FILE *fp = fopen("prime.txt", "w");

    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    for (int num = 2; num <= 100; num++) {
        int is_prime = 1; // 素数フラグ

        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0; // 素数ではない
                break;
            }
        }

        if (is_prime) {
            fprintf(fp, "%d\n", num);
        }
    }

    fclose(fp);
    return 0;
}
