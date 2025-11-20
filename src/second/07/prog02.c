#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *p;
    p = (char*)malloc(5 * sizeof(char));

    strcpy(p, "hoge");
    printf("p = %s\n", p);

    free(p); /* メモリ開放 */
    return 0;
}
