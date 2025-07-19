#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MICROSECONDS_PER_SECOND 1000000

// 画面をクリア
void clear_screen() {
    printf("\033[2J");
}

// カーソルを移動
void cursor_move(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

// カーソルを隠す
void hide_cursor() {
    printf("\033[?25l");
}

// カーソルを表示
void show_cursor() {
    printf("\033[?25h");
}

// 全画面モードを開始
void enter_fullscreen() {
    printf("\033[?1049h"); // 代替画面バッファを使用
}

// 全画面モードを終了
void exit_fullscreen() {
    printf("\033[?1049l"); // 通常画面バッファに戻る
}

// 色をリセット
void reset_color() {
    printf("\033[0m");
}

// n秒間スリープする
void sleep_seconds(float seconds) {
    int microseconds = (int)(seconds * MICROSECONDS_PER_SECOND);
    usleep(microseconds);
}

// ファイルの存在を確認
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}
