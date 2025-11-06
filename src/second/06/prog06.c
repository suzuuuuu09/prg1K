#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("number.txt", "w");

    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < 100; i++) {
        fprintf(fp, "%d\n", i);
    }

    fclose(fp);
    return 0;
}
