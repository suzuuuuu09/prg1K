#include <stdio.h>

int main() {
    int dayOfWeek;
    int time;
    int isOpen = 0;

    printf("曜日? ");
    scanf("%d", &dayOfWeek);
    printf("時間帯? ");
    scanf("%d", &time);

    if (time == 0) {
        if (dayOfWeek == 1 || dayOfWeek == 2 || dayOfWeek == 3 || dayOfWeek == 4 || dayOfWeek == 5) {
            isOpen = 0;
        }
    }

    if (time == 1) {
        if (dayOfWeek == 1 || dayOfWeek == 2 || dayOfWeek == 4 || dayOfWeek == 5 || dayOfWeek == 6) {
            isOpen = 1;
        }
    }
    
    if (isOpen == 1) {
        printf("診察を行っています\n");
    } else {
        printf("診察は行っていません\n");
    }
    // 日=0, 月=1, 火=2, 水=3, 木=4, 金=5, 土=6
    // int dayOfWeek;
    // // 09:00~12:00=0, 13:00~16:00=1
    // int time;
    // int isOpen[7][2] = {
    //     {0, 0}, {1, 1}, {1, 1}, {1, 0}, {1, 1}, {1, 1}, {0, 1}
    // };
    
    // printf("曜日? ");
    // scanf("%d", &dayOfWeek);
    // printf("時間帯? ");
    // scanf("%d", &time);
    
    // printf(isOpen[dayOfWeek][time] ? "診察を行っています" : "診察は行っていません");
    // printf("\n");
    
    // return 0;
}