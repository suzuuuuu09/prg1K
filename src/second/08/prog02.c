/* 問題２ */
/* • 場所を構造体で定義する */
/* • 緯度 */
/* • 経度 */
/* • 住所 */
/* • 場所を２つ⽤意し， */
/* 愛⼯⼤と愛⼯⼤名電の情報で初期化する */
/* • 各場所の情報を表⽰する */
#include <stdio.h>

typedef struct {
    double latitude;
    double longitude;
    char address[256];
} Location;

int main() {
    Location locations[2] = {
        { 35.18345090046129, 137.11302010976638, "愛知工業大学" },
        { 35.1783676506733, 136.94896517029954, "愛工大名電高等学校" }
    };

    for (int i = 0; i < 2; i++) {
        printf("Latitude: %.14f\n", locations[i].latitude);
        printf("Longitude: %.14f\n", locations[i].longitude);
        printf("Address: %s\n", locations[i].address);
        printf("\n");
    }
}
