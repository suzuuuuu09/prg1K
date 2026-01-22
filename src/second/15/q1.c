#include <stdio.h>

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

int main() { return 0; }
