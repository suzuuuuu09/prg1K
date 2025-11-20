#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *p;
    if ((p = (char*)malloc(5 * sizeof(char))) == NULL){
        printf("No enough memory.\n");
        exit(1);
    }

    strcpy(p, "hoge");
    printf("p = %s\n", p);

    free(p); /* メモリ開放 */
    return 0;
}

