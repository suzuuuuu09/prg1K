#include <stdio.h>

typedef struct {
    double latitude;
    double longitude;
    char address[256];
} Location;

int main() {
    Location locations[2] = {
        { 35.18345090046129, 137.11302010976638, "〒470-0356 愛知県豊田市八草町八千草１２４７" },
        { 35.1783676506733, 136.94896517029954, "〒464-0083 愛知県名古屋市千種区若水３丁目２−１２" }
    };

    for (int i = 0; i < 2; i++) {
        printf("Latitude: %.14f\n", locations[i].latitude);
        printf("Longitude: %.14f\n", locations[i].longitude);
        printf("Address: %s\n", locations[i].address);
        printf("\n");
    }
}
