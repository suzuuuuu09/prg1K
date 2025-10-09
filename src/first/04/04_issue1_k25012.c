// BMIの計算を行う
#include <stdio.h>

int main() {
    int height, weight;
    double standardWeight;
    double bmi;

    printf("height? ");
    scanf("%d", &height);

    printf("weight? ");
    scanf("%d", &weight);

    standardWeight = (height - 100) * 0.9;

    double height_m = height / 100.0;  // Convert height from cm to m
    bmi = weight / (height_m * height_m);  // Recalculate BMI with height in meters
    printf("standardWeight = %f\n", standardWeight);
    printf("BMI = %f\n", bmi);

    return 0;
}