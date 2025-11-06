#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int main() {
    char line[MAX];
    FILE *fp = fopen("meibo.txt", "a");

    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        char name[MAX];
        printf("Enter name(!:stop): ");
        scanf("%s", name);
        if (name[0] == '!'){
            break;
        }
        fprintf(fp, "%s\n", name);
    }


    fclose(fp);
    return 0;
}

