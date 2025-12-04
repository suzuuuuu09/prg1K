/* 問題1 */
/* • 学⽣を⼀つの構造体で定義する */
/* • 名前 */
/* • 年齢 */
/* • 学籍番号 */
/* • 学年（1-4の整数でいいです） */
/* • ３⼈の学⽣を初期化し各学⽣の情報を表⽰せよ */
#include <stdio.h>

typedef struct {
    char name[128];
    int age;
    char student_id[20];
    int grade;
} Student;

int main() {
    Student students[3] = {
        { "Yamada", 20, "K25012", 1 },
        { "Tanaka", 18, "K25034", 4 },
        { "Suzuki", 21, "K25056", 2 }
    };

    for (int i = 0; i < 3; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Student ID: %s\n", students[i].student_id);
        printf("Grade: %d\n", students[i].grade);
        printf("\n");
    }
}

