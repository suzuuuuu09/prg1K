/* 問題9 */
/* • 以下の３つのサンプルがどのクラスに属しているか */
/* を推定するプログラムを作成する */
/* • 最も近いサンプルと同じクラスとみなせ */
/* 5.7,4.0,1.2,0.2 */
/* 5.9,2.9,4.2,1.5 */
/* 5.6,2.8,4.8,2.0 */
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

void print_iris_data(struct iris flower) {
    printf("%.1f, %.1f, %.1f, %.1f, %s",
           flower.sepal_length,
           flower.sepal_width,
           flower.petal_length,
           flower.petal_width,
           flower.class);
    printf("\n");
}

void parse_iris_data(char *line, Iris *iris) {
    char *str;

    iris->sepal_length = atof(strtok(line, ","));
    iris->sepal_width = atof(strtok(NULL, ","));
    iris->petal_length = atof(strtok(NULL, ","));
    iris->petal_width = atof(strtok(NULL, ","));
    str = strtok(NULL, ",");

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

double calc_distance(Iris sample, Iris center) {
    return sqrt(pow(sample.sepal_length - center.sepal_length, 2) +
                pow(sample.sepal_width - center.sepal_width, 2) +
                pow(sample.petal_length - center.petal_length, 2) +
                pow(sample.petal_width - center.petal_width, 2));
}

void find_approx_class(Iris sample, Iris *iris_data, int count, char *predicted_class) {
    double min_dist = -1;
    int closest_idx = -1;
    
    for (int i = 0; i < count; i++) {
        double dist = calc_distance(sample, iris_data[i]);
        if (min_dist < 0 || dist < min_dist) {
            min_dist = dist;
            closest_idx = i;
        }
    }
    
    if (closest_idx >= 0) {
        strcpy(predicted_class, iris_data[closest_idx].class);
    }
}

// iris.dataファイルからデータを読み込む
int read_iris_data(const char *filename, Iris *iris_data, int max_count) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Cannot open file.\n");
        return 0;
    }

    char line[50];
    int count = 0;

    while (fgets(line, 50, f) != NULL && count < max_count) {
        parse_iris_data(line, &iris_data[count]);
        count++;
    }

    fclose(f);
    return count;
}

// サンプルのクラスを推定する
void predict_samples(Iris *samples, int sample_count, Iris *iris_data, int data_count) {
    for (int i = 0; i < sample_count; i++) {
        char predicted_class[32];
        find_approx_class(samples[i], iris_data, data_count, predicted_class);
        strcpy(samples[i].class, predicted_class);
    }
}

int main() {
    Iris iris_data[150];
    int count = read_iris_data("iris.data", iris_data, 150);

    Iris samples[3] = {
        {5.7, 4.0, 1.2, 0.2, ""},
        {5.9, 2.9, 4.2, 1.5, ""},
        {5.6, 2.8, 4.8, 2.0, ""}
    };

    predict_samples(samples, 3, iris_data, count);

    for(int i = 0; i < 3; i++) {
        print_iris_data(samples[i]);
    }

    return 0;
}
