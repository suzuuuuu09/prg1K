#include <stdio.h>

int main() {
    double dx;
    printf("dx? ");
    scanf("%lf", &dx);
    printf("dx/2 = %f\n", dx/2);
    
    //doubleをintに変換する
    int nx = (int)dx;
    printf("nx = %d\n", nx);
    printf("nx/2 = %d\n", nx/2);
}