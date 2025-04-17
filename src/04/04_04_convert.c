#include <stdio.h>

int main() {
    int nx, ny;
    printf("nx ny? ");
    scanf("%d %d", &nx, &ny);

    double dx = (double)nx;
    double dy = (double)ny;
    
    printf("nx/ny = %d\n", nx/ny);
    printf("dx/ny = %f\n", dx/ny);
    printf("nx/dy = %f\n", nx/dy);
}