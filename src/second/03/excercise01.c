#include <stdio.h>
#include <math.h>
#define NUMBER 2.0

int getAvgSD(int x, int y, double *avg, double *sd) {
    *avg = (x + y) / NUMBER; // 平均
    double s = ((x - *avg) * (x - *avg) + (y - *avg) * (y - *avg)) / NUMBER;  // 分散
    *sd = sqrt(s); // 標準偏差

    return 0;
}

int main() {
    int a = 0;
    int b = 0;
    double avg = 0;
    double sd = 0;
    
    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);
    
    getAvgSD(a, b, &avg, &sd);
    printf("avg: %f, sd: %f\n", avg, sd);
    
    return 0;
}
