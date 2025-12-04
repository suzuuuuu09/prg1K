/* 問題8 */
/* • 以下の３つのサンプルがどのクラスに属しているか */
/* を推定するプログラムを作成する */
/* • 平均値との距離を測って最も近いクラスとみなせ */
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

void print_iris_avg_sd(struct iris flower, struct iris sum_sq, int n) {
    printf("%s(avg,sd)\n", flower.class);
    printf("sepal_length: (%.2f,%.2f)\n", flower.sepal_length, sqrt(sum_sq.sepal_length / n));
    printf("sepal_width: (%.2f,%.2f)\n", flower.sepal_width, sqrt(sum_sq.sepal_width / n));
    printf("petal_length: (%.2f,%.2f)\n", flower.petal_length, sqrt(sum_sq.petal_length / n));
    printf("petal_width: (%.2f,%.2f)\n", flower.petal_width, sqrt(sum_sq.petal_width / n));
    printf("\n");
}

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

void find_approx_class(Iris sample, Iris setosa_avg, Iris versicolor_avg, Iris virginica_avg, char *predicted_class) {
    double dist_setosa = calc_distance(sample, setosa_avg);
    double dist_versicolor = calc_distance(sample, versicolor_avg);
    double dist_virginica = calc_distance(sample, virginica_avg);
    
    double min_dist = dist_setosa;
    strcpy(predicted_class, "Iris-setosa");
    if (dist_versicolor < min_dist) {
        min_dist = dist_versicolor;
        strcpy(predicted_class, "Iris-versicolor");
    } 
    if (dist_virginica < min_dist) {
        strcpy(predicted_class, "Iris-virginica");
    }
}

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

void calc_class_avg(Iris *iris_data, int count, 
                              Iris *setosa_avg, Iris *versicolor_avg, Iris *virginica_avg) {
    for (int i = 0; i < count; i++) {
        if (strcmp(iris_data[i].class, "Iris-setosa") == 0) {
            add_iris_data(setosa_avg, iris_data[i]);
            setosa_avg->petal_width = setosa_avg->petal_width;
        } else if (strcmp(iris_data[i].class, "Iris-versicolor") == 0) {
            add_iris_data(versicolor_avg, iris_data[i]);
            versicolor_avg->petal_width = versicolor_avg->petal_width;
        } else if (strcmp(iris_data[i].class, "Iris-virginica") == 0) {
            add_iris_data(virginica_avg, iris_data[i]);
            virginica_avg->petal_width = virginica_avg->petal_width;
        }
    }
}

void predict_samples(Iris *samples, int sample_count, 
                     Iris setosa_avg, Iris versicolor_avg, Iris virginica_avg) {
    for (int i = 0; i < sample_count; i++) {
        char predicted_class[32];
        find_approx_class(samples[i], setosa_avg, versicolor_avg, virginica_avg, predicted_class);
        strcpy(samples[i].class, predicted_class);
    }
}

int main() {
    Iris iris_data[150];
    int count = read_iris_data("iris.data", iris_data, 150);

    Iris setosa_avg = {0, 0, 0, 0, "Iris-setosa"};
    Iris versicolor_avg = {0, 0, 0, 0, "Iris-versicolor"};
    Iris virginica_avg = {0, 0, 0, 0, "Iris-virginica"};
    int setosa_num = 0;
    int versicolor_num = 0;
    int virginica_num = 0;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(iris_data[i].class, "Iris-setosa") == 0) {
            add_iris_data(&setosa_avg, iris_data[i]);
            setosa_num++;
        } else if (strcmp(iris_data[i].class, "Iris-versicolor") == 0) {
            add_iris_data(&versicolor_avg, iris_data[i]);
            versicolor_num++;
        } else if (strcmp(iris_data[i].class, "Iris-virginica") == 0) {
            add_iris_data(&virginica_avg, iris_data[i]);
            virginica_num++;
        }
    }

    div_iris_data(&setosa_avg, setosa_num);
    div_iris_data(&versicolor_avg, versicolor_num);
    div_iris_data(&virginica_avg, virginica_num);

    Iris samples[3] = {
        {5.7, 4.0, 1.2, 0.2, ""},
        {5.9, 2.9, 4.2, 1.5, ""},
        {5.6, 2.8, 4.8, 2.0, ""}
    };

    predict_samples(samples, 3, setosa_avg, versicolor_avg, virginica_avg);

    for(int i = 0; i < 3; i++) {
        print_iris_data(samples[i]);
    }

    return 0;
}
