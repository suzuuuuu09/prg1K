#include <stdio.h>
#include <string.h>
#include <time.h>

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
    // 20個のランダムな文字列をもつlistを定義
    char *list[] = {
        "apple",
        "banana",
        "kiwi",
        "grape",
        "watermelon",
        "peach",
        "cherry",
        "blueberry",
        "strawberry",
        "mango",
        "pineapple",
        "raspberry",
        "orange",
        "papaya",
        "cantaloupe",
        "fig",
        "date",
        "pomegranate",
        "tangerine",
        "blackberry"
    };

    const int list_len = sizeof(list) / sizeof(char*);

    printf("ソート前: \n");
    for (int i = 0; i < list_len; i++) {
        printf("%s\n", list[i]);
    }

    // バブルソートを実行
    bubble_str_ptr(list, list_len);

    printf("\nソート後: \n");
    for (int i = 0; i < list_len; i++) {
        printf("%s\n", list[i]);
    }

    // CPU時間の計測
    long cpu_time = clock();

    // チック数を秒に変換
    double seconds = (double)cpu_time / CLOCKS_PER_SEC;

    printf("\nCPU time: %ld clock\n", cpu_time);
    printf("CPU time: %.6f seconds\n", seconds);

    return 0;
}

