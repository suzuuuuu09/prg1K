#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("a[%d] = %d\n", i, arr[i]);
    }
    printf("\n");
}

void randomize(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int n = 10;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    print_array(a, n);

    randomize(a, n);

    printf("Shuffled:\n");
    print_array(a, n);

    return 0;
}
