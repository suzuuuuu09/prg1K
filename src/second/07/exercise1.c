/* 課題 */
/* • 人数入力を受け付ける */
/* • テストの点数を人数分受け付ける */
/* • 動的に確保されたメモリ領域にテストの点数を格納していく */
/* • 平均と標準偏差を出力せよ */
/* • 必ずmallocを使うこと */
/* • 実行結果のスクリーンショットを含めて提出すること */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 平均の計算
double calc_avg(int *scores, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += scores[i];
    }
    return sum / n;
}

// 標準偏差の計算
double calc_stddev(int *scores, int n, double avg) {
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow((scores[i] - avg), 2);
    }
    return sqrt(sum_sq_diff / n);
}

int main() {
    int n, *scores = NULL;

    printf("n? ");
    scanf("%d", &n);

    scores = (int *)malloc(n * sizeof(int));
    if (scores == NULL) {
        printf("No enough memory.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        printf("scores[%d]: ", i);
        scanf("%d", &scores[i]);
    }

    double avg = calc_avg(scores, n);
    double stddev = calc_stddev(scores, n, avg);

    printf("\n --- Result --- \n");
    printf("平均: %f\n", avg);
    printf("標準偏差: %f\n", stddev);

    free(scores); /* メモリ開放 */
    return 0;
}
