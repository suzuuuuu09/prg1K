/* 問題3 */
/* • 構造体をirisを定義し，main関数において ２つの変数 iris1, iris2 を以下の設定で初期化せよ． */
/* • 作成した構造体変数の内容を標準出⼒に表⽰せよ． */
/* iris1: */
/* sepal_length:6.7 */
/* sepal_width:3.0 */
/* petal_length:5.2 */
/* petal_width:2.3 */
/* class:Iris-virginica */
/* iris2: */
/* sepal_length:7.0 */
/* sepal_width:3.2 */
/* petal_length:4.7 */
/* petal_width:1.4 */
/* class:Iris-versicolor */

#include <stdio.h>
struct iris {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char class[20];
};

int print_iris_data(struct iris flower) {
    printf("Sepal Length: %.1f\n", flower.sepal_length);
    printf("Sepal Width: %.1f\n", flower.sepal_width);
    printf("Petal Length: %.1f\n", flower.petal_length);
    printf("Petal Width: %.1f\n", flower.petal_width);
    printf("Class: %s\n", flower.class);
    return 0;
}

int main() {
    struct iris iris1 = {6.7, 3.0, 5.2, 2.3, "Iris-virginica"};
    struct iris iris2 = {7.0, 3.2, 4.7, 1.4, "Iris-versicolor"};

    printf("Iris 1:\n");
    print_iris_data(iris1);

    printf("Iris 2:\n");
    print_iris_data(iris2);

    return 0;
}
