/* 問題5 */
/* • 構造体の配列を⽤意し，Irisデータセットの */
/* ファイル(iris.data)を読み込み，すべてのデータ */
/* を構造体の配列に格納せよ． */
/* • 配列に格納後，配列内の要素の内容をすべて標 */
/* 準出⼒に表⽰せよ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct iris {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char class[32];
} Iris;

// Iris構造体の内容を表示する関数
int print_iris_data(struct iris flower) {
    printf("Sepal Length: %.1f\n", flower.sepal_length);
    printf("Sepal Width: %.1f\n", flower.sepal_width);
    printf("Petal Length: %.1f\n", flower.petal_length);
    printf("Petal Width: %.1f\n", flower.petal_width);
    printf("Class: %s\n", flower.class);
    return 0;
}

// CSV形式のデータを解析してIris構造体にセットする関数
int parse_iris_data(char *line, Iris *iris) {
    char *str;

    str = strtok(line, ",");
    iris->sepal_length = atof(str); // atof: 文字列をdoubleに変換
    str = strtok(NULL, ",");
    iris->sepal_width = atof(str);
    str = strtok(NULL, ",");
    iris->petal_length = atof(str);
    str = strtok(NULL, ",");
    iris->petal_width = atof(str);
    str = strtok(NULL, ",");

    // 改行コードを取り除く
    str[strcspn(str, "\n")] = 0;
    strcpy(iris->class, str);

    return 0;
}

int main() {
    FILE *fp = fopen("iris.data", "r");
    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    Iris iris_data[150];
    char line[50];
    int count = 0;

    while (fgets(line, 50, fp) != NULL && count < 150) {
        parse_iris_data(line, &iris_data[count]);
        count++;
    }

    for (int i = 0; i < count; i++) {
        print_iris_data(iris_data[i]);
    }

    fclose(fp);
    return 0;
}
