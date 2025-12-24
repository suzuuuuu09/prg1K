/* 課題 */
/* • 地震データh2011_eq.csvを構造体の配列として読込み， */
/* 緯度でソートした結果をファイルに出力せよ */
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

// ソート後のデータをファイルに書き出す
void write_eq_file(const char* filename, Earthquake eqs[], int count) {
    // ファイルの読み込み
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("出力ファイルを開けませんでした。\n");
        return;
    }

    for (int j = 0; j < count; j++) {
        fprintf(f, "%d,%d,%d,%.6f,%.6f,%c\n",
                eqs[j].year, eqs[j].month, eqs[j].day,
                eqs[j].lat, eqs[j].lng, eqs[j].pow);
    }

    fclose(f);
}

int main() {
    char line[100];
    Earthquake eqs[MAX_EQ];

    FILE *f = fopen("h2011_eq.csv", "r");
    if (f == NULL) {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }

    int count = 0;
    while (fgets(line, 100, f) != NULL) {
        // 空行や改行のみの行をスキップ
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        // トークンが正しく取得できるかチェック
        if (strchr(line, ',') != NULL) {
            eqs[count] = parse_eq(line);
            count++;
        }
    }

    fclose(f);

    // 緯度をソート(バブルソート)
    for (int j = 0; j < count - 1; j++) {
        for (int k = 0; k < count - j - 1; k++) {
            if (eqs[k].lat > eqs[k + 1].lat) {
                Earthquake temp = eqs[k];
                eqs[k] = eqs[k + 1];
                eqs[k + 1] = temp;
            }
        }
    }

    write_eq_file("h2011_eq_sorted.csv", eqs, count);

    return 0;
}

