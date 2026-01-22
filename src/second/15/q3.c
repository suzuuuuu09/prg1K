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
  printf("Educatio: %.2f\n", p->education_exp);
  printf("Library: %.2f\n", p->library);
  printf("Income: %.2f\n", p->income);
  printf("Faculty: %.2f\n", p->faculty);
}

int main() {
  Pref *p = (Pref *)malloc(sizeof(Pref));
  char line[] = "18,福井県,55.00,739000.00,419054.00,6.00,93266272.00,37.00,"
                "3182.00,20530.00";
  sscanf(line, "%d,%11[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &p->id, p->region,
         &p->math, &p->population, &p->area, &p->univ, &p->education_exp,
         &p->library, &p->income, &p->faculty);

  disp_pref(p);

  free(p);
  return 0;
}
