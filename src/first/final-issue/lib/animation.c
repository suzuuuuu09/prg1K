#include <stdio.h>

// ローディングアニメーション
void loading_animation(float duration) {
    const char *spinner = "|/-\\";
    int spinner_len = 4;
    int iterations = (int)(duration * 10); // 0.1秒間隔で回転
    
    printf("Loading ");
    for (int i = 0; i < iterations; i++) {
        printf("\b%c", spinner[i % spinner_len]);
        fflush(stdout);
        sleep_seconds(0.1f);
    }
}
