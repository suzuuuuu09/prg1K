#include <stdio.h>

int swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    
    return 0;
}

int sort(int *x, int *y) {
    if (*x > *y) {
        swap(x, y);
    }

    return 0;
}

int bubble(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            sort(&arr[j], &arr[j + 1]);
        }
    }

    return 0;
}

int main() {
    int array[5] = {20, 40, 10, 30, 50};
    const int length = sizeof(array) / sizeof(int);

    bubble(array, length);

    for (int i = 0; i < length; i++) {
        printf("a[%d] = %d\n", i, array[i]);
    }

    return 0;
}
