#include <stdio.h>

int main() {
    // 日=0, 月=1, 火=2, 水=3, 木=4, 金=5, 土=6
    int dayOfWeek;
    // 09:00~12:00=0, 13:00~16:00=1
    int time;
    int isOpen[7][2] = {
        {0, 0}, {1, 1}, {1, 1}, {1, 0}, {1, 1}, {1, 1}, {0, 1}
    };
    
    printf("曜日? ");
    scanf("%d", &dayOfWeek);
    printf("時間帯? ");
    scanf("%d", &time);
    
    if(isOpen[dayOfWeek][time]) {
        printf("診察を行っています\n");
    }
    else {
        printf("診察は行っていません\n");
    }
    
    return 0;
}