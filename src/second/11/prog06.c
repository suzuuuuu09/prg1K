/* 問6 */
/* array_testの各要素に対して， */
/* array_learnを用いた１－NNを行い */
/* 推定結果を出力せよ */
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

int main() {

  FILE *fp = fopen("iris.data", "r");
  if (fp == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }

  Iris *array_all = (Iris *)malloc(sizeof(Iris) * 10);
  Iris *array_learn = (Iris *)malloc(sizeof(Iris) * 10);
  Iris *array_test = (Iris *)malloc(sizeof(Iris) * 10);

  char line[50];
  int count = 0;

  while (fgets(line, 50, fp) != NULL && count < 150) {
    if ((array_all = (Iris *)realloc(array_all, sizeof(Iris) * 150)) == NULL) {
      printf("メモリー不足\n");
      exit(1);
    }
    parse_iris_data(line, &array_all[count]);
    count++;
  }

  fclose(fp);

  int learn_length = count / 5 * 4;
  int test_length = count - learn_length;

  if (learn_length > 0) {
    if ((array_learn = (Iris *)realloc(array_learn, sizeof(Iris) * learn_length)) == NULL) {
      printf("メモリー不足\n");
      exit(1);
    }
  }
  if (test_length > 0) {
    if ((array_test = (Iris *)realloc(array_test, sizeof(Iris) * test_length)) == NULL) {
      printf("メモリー不足\n");
      exit(1);
    }
  }

  for (int i = 0; i < learn_length; i++) {
    array_learn[i] = array_all[i];
  }

  for (int i = learn_length; i < count; i++) {
    array_test[i - learn_length] = array_all[i];
  }


  for (int i = 0; i < test_length; i++) {
    double min_distance = -1.0;
    Iris nearest_iris;

    for (int j = 0; j < learn_length; j++) {
      double distance;
      calc_distance(&array_test[i], &array_learn[j], &distance);

      if (min_distance < 0 || distance < min_distance) {
        min_distance = distance;
        nearest_iris = array_learn[j];
      }
    }

    printf("結果: %s\n", nearest_iris.class);
    printf("正解: %s\n", array_test[i].class);
    printf("距離: %.4f\n", min_distance);
    printf("\n");
  }

  free(array_all);
  free(array_learn);
  free(array_test);

  return 0;
}
