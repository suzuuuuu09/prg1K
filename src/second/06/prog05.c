#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int main() {
    char line[MAX];
    FILE *fp = fopen("meibo.txt", "r");

    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    while (fgets(line, MAX, fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
