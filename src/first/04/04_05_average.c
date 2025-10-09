#include <stdio.h>

int main() {
    int h1, h2, h3;
    double average;

    printf("No.1? ");
    scanf("%d", &h1);
    
    printf("No.2? ");
    scanf("%d", &h2);
    
    printf("No.3? ");
    scanf("%d", &h3);

    average = (h1 + h2 + h3) / 3.0;

    printf("average = %f\n", average);

    return 0;
}