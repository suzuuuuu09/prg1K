#include <stdio.h>

int main() {
    double width, height;
    
    printf("width? ");
    scanf("%lf", &width);
    
    printf("height? ");
    scanf("%lf", &height);
    
    double area = width * height;
    printf("area = %f\n", area);
    
    return 0;
}