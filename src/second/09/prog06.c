/* 問題６ */
/* • 全地震データh2011_eq.csvを構造体の配列として */
/* 読込み， */
/* 各震度の回数を出力せよ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EQ 10626

typedef struct {
    int year;
    int month;
    int day;
    double lat; // 緯度
    double lng; // 経度
    char pow;
} Earthquake;

Earthquake parse_eq(char line[]) {
    Earthquake e;
    char *token;

    e.year = atoi(strtok(line, ","));
    e.month = atoi(strtok(NULL, ","));
    e.day = atoi(strtok(NULL, ","));
    e.lat = atof(strtok(NULL, ","));
    e.lng = atof(strtok(NULL, ","));
    token = strtok(NULL, ",\n");
    e.pow = (token != NULL) ? token[0] : '0';

    return e;
}

void print_eq(const Earthquake* eq) {
    printf("発生日: %04d-%02d-%02d\n", eq->year, eq->month, eq->day);
    printf("緯度: %.6f\n", eq->lat);
    printf("経度: %.6f\n", eq->lng);
    printf("震度: %c\n", eq->pow);
    printf("\n");
}

int main() {
    char line[100];
    Earthquake eqs[MAX_EQ];

    FILE *f = fopen("h2011_eq.csv", "r");
    if (f == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    int i = 0;
    while (fgets(line, 100, f) != NULL) {
        // 空行や改行のみの行をスキップ
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        // トークンが正しく取得できるかチェック
        if (strchr(line, ',') != NULL) {
            eqs[i] = parse_eq(line);
            i++;
        }
    }

    fclose(f);

    int pow_count[16] = {0};

    for(int j = 0; j < i; j++) {
        int index = 0;
        switch(eqs[j].pow) {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                index = eqs[j].pow - 'A' + 8;
                break;
            default:
                index = eqs[j].pow - '0';
                break;
        }
        pow_count[index]++;
    }

    printf("震度1: %d回\n", pow_count[1]);
    printf("震度2: %d回\n", pow_count[2]);
    printf("震度3: %d回\n", pow_count[3]);
    printf("震度4: %d回\n", pow_count[4]);
    printf("震度5弱: %d回\n", pow_count[8]);
    printf("震度5強: %d回\n", pow_count[9]);
    printf("震度6弱: %d回\n", pow_count[10]);
    printf("震度6強: %d回\n", pow_count[11]);
    printf("震度7: %d回\n", pow_count[7]);


    return 0;
}

