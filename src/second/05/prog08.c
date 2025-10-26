#include <stdio.h>
#include <string.h>

int swap_str_ptr(char **a, char **b) {
    char *temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

int main() {
    char *a = "AB";
    char *b = "XY";

    printf("a = %s, b = %s\n", a, b);
    printf("swap!!!!!!!\n");
    swap_str_ptr(&a, &b);
    printf("a = %s, b = %s\n", a, b);

    return 0;
}
