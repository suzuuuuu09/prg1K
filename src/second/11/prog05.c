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

  for (int i = 0; i < learn_length; i++) {
    unsigned long size = sizeof(Iris) * (i + 1);
    array_learn[i] = array_all[i];
  }

  for (int i = learn_length; i < count; i++) {
    unsigned long size = sizeof(Iris) * (i - learn_length + 1);
    array_test[i - learn_length] = array_all[i];
  }

  printf("array_learn:\n");
  for (int i = 0; i < learn_length; i++) {
    print_iris_data(array_learn[i]);
  }
  printf("\n");

  printf("array_test:\n");
  for (int i = 0; i < count - learn_length; i++) {
    print_iris_data(array_test[i]);
  }

  free(array_all);
  free(array_learn);
  free(array_test);

  return 0;
}
