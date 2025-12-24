/* 課題 */
/* • h2011_eq.csv を用い，緯度（latitude）2°刻みで， */
/* その緯度での地震の回数を出力するプログラムを作成せよ． */

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

	// 緯度の範囲を取得する
	int lat_range_min = eqs[0].lat - ((int)eqs[0].lat % 2);
	int lat_range_max = eqs[count - 1].lat + (2 - ((int)eqs[count - 1].lat % 2));

	// 緯度2°刻みで地震の回数をカウント
	for (int lat = lat_range_min; lat < lat_range_max; lat += 2) {
		int eq_count = 0;
		for (int i = 0; i < count; i++) {
			if (eqs[i].lat >= lat && eqs[i].lat < lat + 2) {
				eq_count++;
			}
		}
		printf("緯度 %.0f°〜%.0f° の地震の回数: %d\n", (double)lat, (double)(lat + 2), eq_count);
	}

	return 0;
}




