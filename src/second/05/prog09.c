#include <stdio.h>
#include <string.h>

int swap_str_ptr(char **a, char **b) {
    char *temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

int sort_str_ptr(char **a, char **b) {
    size_t a_len = strlen(*a);
    size_t b_len = strlen(*b);

    if(b_len < a_len) {
        swap_str_ptr(a, b);
    }

    return 0;
}

int main() {
    char *a = "abcde";
    char *b = "xyz";

    printf("a = %s, b = %s\n", a, b);

    printf("----------- Sort ----------\n");
    sort_str_ptr(&a, &b);

    printf("a = %s, b = %s\n", a, b);

    return 0;
}

