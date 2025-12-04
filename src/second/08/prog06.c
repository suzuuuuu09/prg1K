/* 問題6 */
/* • classごとに各特徴量の平均値を出⼒せよ． */
/* 出⼒例︓ */
/* Iris-setosa(avg) */
/* sepal_length: (**.**) */
/* sepal_width: (**.**) */
/* petal_length: (**.**) */
/* petal_width: (**.**) */
/* Iris-versicolor(avg) */
/* sepal_length: (**.**) */
/* sepal_width: (**.**) */
/* petal_length: (**.**) */
/* petal_width: (**.**) */

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

// データの平均値を表示する関数
int print_iris_data(struct iris flower) {
    printf("%s(avg)\n", flower.class);
    printf("sepal_length: (%.2f)\n", flower.sepal_length);
    printf("sepal_width: (%.2f)\n", flower.sepal_width);
    printf("petal_length: (%.2f)\n", flower.petal_length);
    printf("petal_width: (%.2f)\n", flower.petal_width);
    printf("\n");
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

int div_iris_data(Iris *iris, int n) {
    iris->sepal_length /= n;
    iris->sepal_width /= n;
    iris->petal_length /= n;
    iris->petal_width /= n;
    return 0;
}

int add_iris_data(Iris *a, Iris b) {
    a->sepal_length += b.sepal_length;
    a->sepal_width += b.sepal_width;
    a->petal_length += b.petal_length;
    a->petal_width += b.petal_width;
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

    while (fgets(line, 50, fp) != NULL) {
        parse_iris_data(line, &iris_data[count]);
        count++;
    }

    // クラスごとに合計値を計算
    Iris setosa = {0, 0, 0, 0, "Iris-setosa"};
    Iris versicolor = {0, 0, 0, 0, "Iris-versicolor"};
    Iris virginica = {0, 0, 0, 0, "Iris-virginica"};
    int setosa_num = 0;
    int versicolor_num = 0;
    int virginica_num = 0;
    
    for (int i = 0; i < count; i++) {
        Iris iris = iris_data[i];
        if (strcmp(iris.class, "Iris-setosa") == 0) {
            add_iris_data(&setosa, iris);
            setosa_num++;
        } else if (strcmp(iris.class, "Iris-versicolor") == 0) {
            add_iris_data(&versicolor, iris);
            versicolor_num++;
        } else if (strcmp(iris.class, "Iris-virginica") == 0) {
            add_iris_data(&virginica, iris);
            virginica_num++;
        }
    }

    div_iris_data(&setosa, setosa_num);
    div_iris_data(&versicolor, versicolor_num);
    div_iris_data(&virginica, virginica_num);
    print_iris_data(setosa);
    print_iris_data(versicolor);
    print_iris_data(virginica);

    fclose(fp);
    return 0;
}
