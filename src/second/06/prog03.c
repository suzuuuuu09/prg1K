#include <stdio.h>
#include <math.h>

// 距離を計算する関数
int calc_distance(int x1, int y1, int x2, int y2) {
    double pow_x = pow((x2 - x1), 2);
    double pow_y = pow((y2 - y1), 2);
    double distance = sqrt(pow_x + pow_y);

    return distance;
}

int main() {
    int x1 = 10;
    int y1 = 20;
    int x2 = 200;
    int y2 = 50;

    double distance = calc_distance(x1, y1, x2, y2);
    printf("点(%d, %d)と点(%d, %d)の距離: %f\n", x1, y1, x2, y2, distance);
}
