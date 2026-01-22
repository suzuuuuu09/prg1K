#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PREFS 47

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

Pref calc_avg(Pref *array, int size, int id, const char *region) {
  Pref avg = {0};
  for (int i = 0; i < size; i++) {
    avg.math += array[i].math;
    avg.population += array[i].population;
    avg.area += array[i].area;
    avg.univ += array[i].univ;
    avg.education_exp += array[i].education_exp;
    avg.library += array[i].library;
    avg.income += array[i].income;
    avg.faculty += array[i].faculty;
  }
  avg.id = id;
  strncpy(avg.region, region, sizeof(avg.region) - 1);
  avg.math /= size;
  avg.population /= size;
  avg.area /= size;
  avg.univ /= size;
  avg.education_exp /= size;
  avg.library /= size;
  avg.income /= size;
  avg.faculty /= size;

  return avg;
}

int main() {
  Pref array[MAX_PREFS];
  read_prefs("statistics.csv", array, MAX_PREFS);
  // for (int i = 0; i < MAX_PREFS; i++) {
  //   disp_pref(&array[i]);
  //   printf("\n");
  // }
  Pref avg = calc_avg(array, MAX_PREFS, 48, "平均");
  disp_pref(&avg);

  return 0;
}
