/* 課題 */
/* • Irisの1-NN分類アルゴリズムを */
/* ５分割クロスバリデーションで評価し */
/* 結果を混同行列で表示せよ */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct iris {
  double sepal_length;
  double sepal_width;
  double petal_length;
  double petal_width;
  char class[32];
} Iris;

// Iris構造体の内容を表示する関数
int print_iris_data(struct iris flower) {
  printf("%.1f, %.1f, %.1f, %.1f, %s\n", flower.sepal_length,
         flower.sepal_width, flower.petal_length, flower.petal_width,
         flower.class);
  return 0;
}

void randomize(Iris arr[], int size) {
  srand((unsigned int)time(NULL));
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);

    Iris temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
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

  // 改行コードとCRコードを取り除く
  str[strcspn(str, "\r\n")] = 0;
  strcpy(iris->class, str);

  return 0;
}

double calc_distance(Iris *a, Iris *b, double *distance) {
  *distance = 0.0;
  *distance +=
      (a->sepal_length - b->sepal_length) * (a->sepal_length - b->sepal_length);
  *distance +=
      (a->sepal_width - b->sepal_width) * (a->sepal_width - b->sepal_width);
  *distance +=
      (a->petal_length - b->petal_length) * (a->petal_length - b->petal_length);
  *distance +=
      (a->petal_width - b->petal_width) * (a->petal_width - b->petal_width);
  *distance = sqrt(*distance);

  return *distance;
}

int class_to_index(const char *class_name) {
  if (strcmp(class_name, "Iris-setosa") == 0) {
    return 0;
  } else if (strcmp(class_name, "Iris-versicolor") == 0) {
    return 1;
  } else if (strcmp(class_name, "Iris-virginica") == 0) {
    return 2;
  } else {
    return -1; // Unknown class
  }
}

void print_matrix(double matrix[3][3]) {
  printf("混同行列 (縦: 正解, 横: 推定)\n");
  printf("                Iris-setosa  Iris-versicolor  Iris-virginica\n");
  printf("Iris-setosa      %.2f         %.2f          %.2f\n", matrix[0][0],
         matrix[0][1], matrix[0][2]);
  printf("Iris-versicolor  %.2f         %.2f          %.2f\n", matrix[1][0],
         matrix[1][1], matrix[1][2]);
  printf("Iris-virginica   %.2f         %.2f          %.2f\n", matrix[2][0],
         matrix[2][1], matrix[2][2]);
  printf("\n");
}

void print_accuracy(int correct, int total) {
  double accuracy = (double)correct / total * 100.0;
  printf("正解率: %.2f%%\n", accuracy);
}

Iris one_nn(Iris *array_learn, int learn_length, Iris target) {
  double min_distance = -1.0;
  Iris nearest_iris;

  for (int j = 0; j < learn_length; j++) {
    double distance;
    calc_distance(&target, &array_learn[j], &distance);

    if (min_distance < 0 || distance < min_distance) {
      min_distance = distance;
      nearest_iris = array_learn[j];
    }
  }
  return nearest_iris;
}

int main() {
  FILE *fp = fopen("Iris.data", "r");
  if (fp == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }

  Iris *array_all = (Iris *)malloc(sizeof(Iris) * 10);

  char line[50];
  int num = 0;
  int n = 5; // 分割数

  while (fgets(line, 50, fp) != NULL && num < 150) {
    if ((array_all = (Iris *)realloc(array_all, sizeof(Iris) * 150)) == NULL) {
      printf("メモリー不足\n");
      exit(1);
    }
    parse_iris_data(line, &array_all[num]);
    num++;
  }
  fclose(fp);

  randomize(array_all, num);

  int div_size = num / n;

  int correct = 0;
  double confusion_matrix[3][3] = {0};
  for (int k = 0; k < n; k++) {
    int learn_length = num - div_size;
    int test_length = div_size;

    Iris *array_learn = (Iris *)malloc(sizeof(Iris) * learn_length);
    Iris *array_test = (Iris *)malloc(sizeof(Iris) * test_length);

    int learn_index = 0;
    int test_index = 0;
    for (int i = 0; i < num; i++) {
      if (i >= k * div_size && i < (k + 1) * div_size) {
        array_test[test_index++] = array_all[i];
      } else {
        array_learn[learn_index++] = array_all[i];
      }
    }

    for (int i = 0; i < test_length; i++) {
      Iris predicted = one_nn(array_learn, learn_length, array_test[i]);
      int index_learn = class_to_index(predicted.class);
      int index_test = class_to_index(array_test[i].class);
      confusion_matrix[index_test][index_learn] += 1.0;
      if (strcmp(predicted.class, array_test[i].class) == 0) {
        correct++;
      }
    }

    free(array_learn);
    free(array_test);
  }
  for (int i = 0; i < 3; i++) {
    double row_sum = 0.0;
    for (int j = 0; j < 3; j++) {
      row_sum += confusion_matrix[i][j];
    }
    for (int j = 0; j < 3; j++) {
      if (row_sum > 0) {
        confusion_matrix[i][j] /= row_sum;
      }
    }
  }

  print_matrix(confusion_matrix);
  print_accuracy(correct, num);

  free(array_all);

  return 0;
}
