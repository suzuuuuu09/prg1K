// k-NNを使ったサンプルデータのクラス予測を行う
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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_indices_by_distance(double *distances, int *indices, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (distances[indices[i]] > distances[indices[j]]) {
                swap(&indices[i], &indices[j]);
            }
        }
    }
}

void count_classes(Iris *iris_data, int *indices, int k, int *class_count) {
    for (int i = 0; i < k; i++) {
        int idx = indices[i];
        if (strcmp(iris_data[idx].class, "Iris-setosa") == 0) {
            class_count[0]++;
        } else if (strcmp(iris_data[idx].class, "Iris-versicolor") == 0) {
            class_count[1]++;
        } else if (strcmp(iris_data[idx].class, "Iris-virginica") == 0) {
            class_count[2]++;
        }
    }
}

// 最も多いクラスのインデックスを返す
int find_max_class(int *class_count) {
    int max_count = class_count[0];
    int predicted_idx = 0;
    for (int i = 1; i < 3; i++) {
        if (class_count[i] > max_count) {
            max_count = class_count[i];
            predicted_idx = i;
        }
    }
    return predicted_idx;
}

// クラス名を設定する
void set_class_name(int predicted_idx, char *predicted_class) {
    if (predicted_idx == 0) {
        strcpy(predicted_class, "Iris-setosa");
    } else if (predicted_idx == 1) {
        strcpy(predicted_class, "Iris-versicolor");
    } else if (predicted_idx == 2) {
        strcpy(predicted_class, "Iris-virginica");
    }
}

// k-NNでサンプルのクラスを推定するっ
void find_approx_class_knn(Iris sample, Iris *iris_data, int count, char *predicted_class, int k) {
    double distances[150];
    for (int i = 0; i < count; i++) {
        distances[i] = calc_distance(sample, iris_data[i]);
    }

    int indices[150];
    for (int i = 0; i < count; i++) {
        indices[i] = i;
    }
    sort_indices_by_distance(distances, indices, count);

    int class_count[3] = {0, 0, 0};
    count_classes(iris_data, indices, k, class_count);

    int predicted_idx = find_max_class(class_count);
    set_class_name(predicted_idx, predicted_class);
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
void predict_samples(Iris *samples, int sample_count, Iris *iris_data, int data_count, int k) {
    for (int i = 0; i < sample_count; i++) {
        char predicted_class[32];
        find_approx_class_knn(samples[i], iris_data, data_count, predicted_class, k);
        strcpy(samples[i].class, predicted_class);
    }
}

int main() {
    int k = 0;
    printf("k? ");
    scanf("%d", &k);

    Iris iris_data[150];
    int count = read_iris_data("iris.data", iris_data, 150);

    Iris samples[3] = {
        {5.7, 4.0, 1.2, 0.2, ""},
        {5.9, 2.9, 4.2, 1.5, ""},
        {5.6, 2.8, 4.8, 2.0, ""}
    };

    predict_samples(samples, 3, iris_data, count, k);

    for(int i = 0; i < 3; i++) {
        print_iris_data(samples[i]);
    }

    return 0;
}
