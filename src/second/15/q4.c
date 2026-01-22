#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pref {
  int id;
  char region[16];
  double math;          // 数学点数
  double population;    // 人口
  double area;          // 総面積
  double univ;          // 大学数
  double education_exp; // 財政教育数
  double library;       // 図書館数
  double income;        // 1人あたり所得
  double faculty;       // 教員数
} Pref;

void disp_pref(Pref *p) {
  printf("ID: %d\n", p->id);
  printf("Region: %s\n", p->region);
  printf("Math: %.2f\n", p->math);
  printf("Population: %.2f\n", p->population);
  printf("Area: %.2f\n", p->area);
  printf("University: %.2f\n", p->univ);
  printf("Education Expenditure: %.2f\n", p->education_exp);
  printf("Library: %.2f\n", p->library);
  printf("Income: %.2f\n", p->income);
  printf("Faculty: %.2f\n", p->faculty);
}

void parse_pref(Pref *p, const char *line) {
  // NOTE: [^,]はカンマ以外の文字列を意味する
  // 書かないとなぜか読み込めな
  sscanf(line, "%d,%11[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &p->id, p->region,
         &p->math, &p->population, &p->area, &p->univ, &p->education_exp,
         &p->library, &p->income, &p->faculty);
}

void read_prefs(const char *filename, Pref *array, int max_prefs) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("ファイルが読み込めません");
    return;
  }

  char line[256];
  int count = 0;
  while (fgets(line, sizeof(line), file) != NULL && count < max_prefs) {
    parse_pref(&array[count], line);
    count++;
  }

  fclose(file);
}

int main() {
  Pref array[47];
  read_prefs("statistics.csv", array, 47);
  for (int i = 0; i < 47; i++) {
    disp_pref(&array[i]);
    printf("\n");
  }

  return 0;
}
