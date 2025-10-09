#include <stdio.h>

int main() {
    int total, legs, crane, tortoise;
    printf("total? ");
    scanf("%d", &total);
    printf("legs? ");
    scanf("%d", &legs);

    crane = (4 * total - legs) / 2;
    tortoise = total - crane;
    if (crane < 0 || tortoise < 0 || legs % 2 != 0) {
        printf("cannot be combined\n");
    } else {
        printf("crane = %d, tortoise = %d\n", crane, tortoise);
    }
}
