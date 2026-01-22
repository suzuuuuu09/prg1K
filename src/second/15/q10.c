// NOTE: この問題ムズすぎィ！
#include <math.h>
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

Pref calc_var(Pref *array, int size, Pref *avg, int id, const char *region) {
  Pref var = {0};
  for (int i = 0; i < size; i++) {
    var.math += pow((array[i].math - avg->math), 2);
    var.population += pow((array[i].population - avg->population), 2);
    var.area += pow((array[i].area - avg->area), 2);
    var.univ += pow((array[i].univ - avg->univ), 2);
    var.education_exp += pow((array[i].education_exp - avg->education_exp), 2);
    var.library += pow((array[i].library - avg->library), 2);
    var.income += pow((array[i].income - avg->income), 2);
    var.faculty += pow((array[i].faculty - avg->faculty), 2);
  }
  var.id = id;
  strncpy(var.region, region, sizeof(var.region) - 1);
  var.math /= size;
  var.population /= size;
  var.area /= size;
  var.univ /= size;
  var.education_exp /= size;
  var.library /= size;
  var.income /= size;
  var.faculty /= size;

  return var;
}

Pref calc_sd(Pref *var, int id, const char *region) {
  // NOTE: 標準偏差 = √分散
  Pref sd = {0};
  sd.id = id;
  strncpy(sd.region, region, sizeof(sd.region) - 1);
  sd.math = sqrt(var->math);
  sd.population = sqrt(var->population);
  sd.area = sqrt(var->area);
  sd.univ = sqrt(var->univ);
  sd.education_exp = sqrt(var->education_exp);
  sd.library = sqrt(var->library);
  sd.income = sqrt(var->income);
  sd.faculty = sqrt(var->faculty);

  return sd;
}

Pref calc_cov(Pref *array, Pref *avg, int size, int id, const char *region) {
  // mathとの共分散をもとめる
  // NOTE: 共分散 = 1/n * Σ((x - 平均x) * (y - 平均y))
  Pref cov = {0};
  for (int i = 0; i < size; i++) {
    cov.math += (array[i].math - avg->math) * (array[i].math - avg->math);
    cov.population +=
        (array[i].population - avg->population) * (array[i].math - avg->math);
    cov.area += (array[i].area - avg->area) * (array[i].math - avg->math);
    cov.univ += (array[i].univ - avg->univ) * (array[i].math - avg->math);
    cov.education_exp += (array[i].education_exp - avg->education_exp) *
                         (array[i].math - avg->math);
    cov.library +=
        (array[i].library - avg->library) * (array[i].math - avg->math);
    cov.income += (array[i].income - avg->income) * (array[i].math - avg->math);
    cov.faculty +=
        (array[i].faculty - avg->faculty) * (array[i].math - avg->math);
  }

  cov.id = id;
  strncpy(cov.region, region, sizeof(cov.region) - 1);
  cov.math /= size;
  cov.population /= size;
  cov.area /= size;
  cov.univ /= size;
  cov.education_exp /= size;
  cov.library /= size;
  cov.income /= size;
  cov.faculty /= size;

  return cov;
}

Pref calc_corrcoef(Pref *sd, Pref *cov, int size, int id, const char *region) {
  // NOTE: 相関係数 = 共分散 / (x標準偏差) * (y標準偏差)
  Pref r = {0};

  r.id = id;
  strncpy(r.region, region, sizeof(r.region) - 1);
  r.math = cov->math / ((sd->math) * sd->math);
  r.population = cov->population / ((sd->population) * sd->math);
  r.area = cov->area / ((sd->area) * sd->math);
  r.univ = cov->univ / ((sd->univ) * sd->math);
  r.education_exp = cov->education_exp / ((sd->education_exp) * sd->math);
  r.library = cov->library / ((sd->library) * sd->math);
  r.income = cov->income / ((sd->income) * sd->math);
  r.faculty = cov->faculty / ((sd->faculty) * sd->math);

  return r;
}

void find_max_corrcoef(Pref *r) {
  double max_value = r->population;
  char max_elem[64] = "総人口【人】";

  // 数学は自己相関なのでスキップ
  // マイナスの符号でも使えるようにfabs(絶対値)を使う
  if (fabs(r->area) > fabs(max_value)) {
    max_value = r->area;
    strcpy(max_elem, "総面積【ha】");
  } else if (fabs(r->univ) > fabs(max_value)) {
    max_value = r->univ;
    strcpy(max_elem, "大学数【校】");
  } else if (fabs(r->education_exp) > fabs(max_value)) {
    max_value = r->education_exp;
    strcpy(max_elem, "財政教育費【千円】");
  } else if (fabs(r->library) > fabs(max_value)) {
    max_value = r->library;
    strcpy(max_elem, "図書館数【館】");
  } else if (fabs(r->income) > fabs(max_value)) {
    max_value = r->income;
    strcpy(max_elem, "１人当たり県民所得【千円】");
  } else if (fabs(r->faculty) > fabs(max_value)) {
    max_value = r->faculty;
    strcpy(max_elem, "教員数【人】");
  }

  char line[256];
  // sprintf(line, "%s,%.2f\n", max_elem, max_value);
  sprintf(line, "%s,%.2f", max_elem, max_value);
  FILE *f_output = fopen("q10.txt", "w");
  if (f_output == NULL) {
    perror("ファイルを読み込めません");
    return;
  }

  fprintf(f_output, line);

  fclose(f_output);
}

int main() {
  Pref array[MAX_PREFS];
  read_prefs("statistics.csv", array, MAX_PREFS);

  Pref avg = calc_avg(array, MAX_PREFS, 48, "平均");
  Pref var = calc_var(array, MAX_PREFS, &avg, 49, "分散");
  Pref sd = calc_sd(&var, 50, "標準偏差");
  Pref cov = calc_cov(array, &avg, MAX_PREFS, 51, "共分散");
  Pref r = calc_corrcoef(&sd, &cov, MAX_PREFS, 52, "相関係数");
  disp_pref(&r);
  find_max_corrcoef(&r);

  return 0;
}
