/* 問題４ */
/* • 地震データh2011_eq.csvを構造体の配列として */
/* 読み込む */
/* • ３月１１日の地震だけを出力する */

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

    for (int j = 0; j < i; j++) {
        if(eqs[j].month == 3 && eqs[j].day == 11)
            print_eq(&eqs[j]);
    }

    return 0;
}
