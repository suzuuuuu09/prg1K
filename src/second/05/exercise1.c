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

int bubble_str_ptr(char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            sort_str_ptr(&arr[j], &arr[j + 1]);
        }
    }

    return 0;
}

int main() {
    char *list[] = {"hoge", "abc","xy","fugagaga"};
    /* char *list[] = {"banana", "apple", "grape", "kiwi", "strawberry", "fig", "blueberry"}; */

    const int list_len = sizeof(list) / sizeof(char*);
    bubble_str_ptr(list, list_len);
    for (int i = 0; i < list_len; i++) {
        printf("list[%d] = %s\n", i, list[i]);
    }

    return 0;
}
