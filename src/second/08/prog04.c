/* 問題4 */
/* • 以下の⽂字列を分割してiris構造体にセットせよ． */
/* • セットした構造体変数の内容を標準出⼒に表⽰せよ． */
/* 例︓ */
/* char line[50]="5.7,2.9,4.2,1.3,Iris-versicolor¥n"; */
/* この例では，fgetsでファイルから1⾏を読み込んだ時と同様 ，⾏の最後に改⾏コード(¥n)が 含まれている． */
/* csvを分割して構造体の内容を埋めていく際，iris構造体のclass変数の値（⽂字列）に */
/* 最後の改⾏コードが含まれないようにしておくと以降の処理（⽂字列マッチング等）が単 */
/* 純化できる． */
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
    char line[50] = "5.7,2.9,4.2,1.3,Iris-versicolor\n";

    // strtokで分割
    char *str;
    Iris iris;

    parse_iris_data(line, &iris);
    print_iris_data(iris);

    return 0;
}
