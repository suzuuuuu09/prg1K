/* 問題7 */
/* • classごとに各特徴量の標準偏差も合わせて出⼒せよ */
/* 出⼒例︓ */
/* Iris-setosa(avg,sd) */
/* sepal_length: (**.**,**.**) */
/* sepal_width: (**.**,**.**) */
/* petal_length: (**.**,**.**) */
/* petal_width: (**.**,**.**) */
/* Iris-versicolor(avg,sd) */
/* sepal_length: (**.**,**.**) */
/* sepal_width: (**.**,**.**) */
/* petal_length: (**.**,**.**) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct iris {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char class[32];
} Iris;

void print_iris_avg_sd(struct iris flower, struct iris sum_sq, int n) {
    printf("%s(avg,sd)\n", flower.class);
    printf("sepal_length: (%.2f,%.2f)\n", flower.sepal_length, sqrt(sum_sq.sepal_length / n));
    printf("sepal_width: (%.2f,%.2f)\n", flower.sepal_width, sqrt(sum_sq.sepal_width / n));
    printf("petal_length: (%.2f,%.2f)\n", flower.petal_length, sqrt(sum_sq.petal_length / n));
    printf("petal_width: (%.2f,%.2f)\n", flower.petal_width, sqrt(sum_sq.petal_width / n));
    printf("\n");
}

// CSV形式のデータを解析してIris構造体にセットする関数
void parse_iris_data(char *line, Iris *iris) {
    char *str;

    iris->sepal_length = atof(strtok(line, ",")); // atof: 文字列をdoubleに変換
    iris->sepal_width = atof(strtok(NULL, ","));
    iris->petal_length = atof(strtok(NULL, ","));
    iris->petal_width = atof(strtok(NULL, ","));
    str = strtok(NULL, ",");

    // 改行コードを取り除く
    str[strcspn(str, "\n")] = 0;
    strcpy(iris->class, str);
}

void div_iris_data(Iris *iris, int n) {
    iris->sepal_length /= n;
    iris->sepal_width /= n;
    iris->petal_length /= n;
    iris->petal_width /= n;
}

void add_iris_data(Iris *a, Iris b) {
    a->sepal_length += b.sepal_length;
    a->sepal_width += b.sepal_width;
    a->petal_length += b.petal_length;
    a->petal_width += b.petal_width;
}

void compute_sd(Iris *sd, Iris iris, Iris avg) {
    sd->sepal_length += pow(iris.sepal_length - avg.sepal_length, 2);
    sd->sepal_width += pow(iris.sepal_width - avg.sepal_width, 2);
    sd->petal_length += pow(iris.petal_length - avg.petal_length, 2);
    sd->petal_width += pow(iris.petal_width - avg.petal_width, 2);
}

int main() {
    FILE *f = fopen("iris.data", "r");
    if (f == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    Iris iris_data[150];
    char line[50];
    int count = 0;

    while (fgets(line, 50, f) != NULL) {
        parse_iris_data(line, &iris_data[count]);
        count++;
    }

    // クラスごとに合計値を計算
    Iris setosa_avg = {0, 0, 0, 0, "Iris-setosa"};
    Iris versicolor_avg = {0, 0, 0, 0, "Iris-versicolor"};
    Iris virginica_avg = {0, 0, 0, 0, "Iris-virginica"};
    int setosa_num = 0;
    int versicolor_num = 0;
    int virginica_num = 0;
    
    for (int i = 0; i < count; i++) {
        Iris iris = iris_data[i];
        if (strcmp(iris.class, "Iris-setosa") == 0) {
            add_iris_data(&setosa_avg, iris);
            setosa_num++;
        } else if (strcmp(iris.class, "Iris-versicolor") == 0) {
            add_iris_data(&versicolor_avg, iris);
            versicolor_num++;
        } else if (strcmp(iris.class, "Iris-virginica") == 0) {
            add_iris_data(&virginica_avg, iris);
            virginica_num++;
        }
    }

    div_iris_data(&setosa_avg, setosa_num);
    div_iris_data(&versicolor_avg, versicolor_num);
    div_iris_data(&virginica_avg, virginica_num);

    Iris setosa_sd = {0, 0, 0, 0, "Iris-setosa"};
    Iris versicolor_sd = {0, 0, 0, 0, "Iris-versicolor"};
    Iris virginica_sd = {0, 0, 0, 0, "Iris-virginica"};

    // 標準偏差の計算
    for (int i = 0; i < count; i++) {
        Iris iris = iris_data[i];
        if (strcmp(iris.class, "Iris-setosa") == 0) {
            compute_sd(&setosa_sd, iris, setosa_avg);
        } else if (strcmp(iris.class, "Iris-versicolor") == 0) {
            compute_sd(&versicolor_sd, iris, versicolor_avg);
        } else if (strcmp(iris.class, "Iris-virginica") == 0) {
            compute_sd(&virginica_sd, iris, virginica_avg);
        }
    }

    print_iris_avg_sd(setosa_avg, setosa_sd, setosa_num);
    print_iris_avg_sd(versicolor_avg, versicolor_sd, versicolor_num);
    print_iris_avg_sd(virginica_avg, virginica_sd, virginica_num);

    fclose(f);
    return 0;
}
