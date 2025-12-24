#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int month;
    int day;
    double lat; // 緯度
    double lng; // 経度
    char pow;
} Earthquake;

Earthquake parse_line(char line[]) {
    Earthquake eq;
    eq.year = atoi(strtok(line, ","));
    eq.month = atoi(strtok(NULL, ","));
    eq.day = atoi(strtok(NULL, ","));
    eq.lat = atof(strtok(NULL, ","));
    eq.lng = atof(strtok(NULL, ","));
    eq.pow = *strtok(NULL, ",");

    return eq;
}

void print_eq(const Earthquake* eq) {
    printf("発生日: %04d-%02d-%02d\n", eq->year, eq->month, eq->day);
    printf("緯度: %.6f\n", eq->lat);
    printf("経度: %.6f\n", eq->lng);
    printf("震度: %c\n", eq->pow);
    printf("\n");
}

int main() {
    char line[] = "2011,3,11,36.623000,141.413667,2";

    Earthquake eq = parse_line(line);
    print_eq(&eq);

    return 0;
}
