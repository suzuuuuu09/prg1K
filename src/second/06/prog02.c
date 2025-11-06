#include <stdio.h>
#include <math.h>

int calc_area(int radius) {
    return M_PI * radius * radius;
}

int calc_circumference(int radius) {
    return 2 * M_PI * radius;
}

int main() {
    int r = 10;
    
    double area = calc_area(r);
    printf("半径%dの円の面積: %f\n", r, area);

    double circumference = calc_circumference(r);
    printf("半径%dの円の周囲長: %f\n", r, circumference);
}
