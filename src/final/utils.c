#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
    * @brief 引数のテキストが何行あるか数える関数
    * @param text 対象の文字列
    * @return 行数
 */
extern int count_text_line(const char* text) {
    int line_count = 1; // 最低1行はある
    size_t text_length = strlen(text);
    
    for (size_t i = 0; i < text_length; i++) {
        if (text[i] == '\n') {
            line_count++;
        }
    }
    
    return line_count;
}

/**
    * @brief 画面をクリアする関数
    * @note エスケープシーケンスを使用し、ターミナル内に表示していた内容を全て削除する。
 */
extern void clear_screen() {
    // エスケープシーケンスを使用して画面をクリア
    printf("\033[H\033[J");
    fflush(stdout); // 出力を即座に反映
}

/**
    * @brief カーソルを指定位置に移動する関数
    * @param x X座標（列）
    * @param y Y座標（行）
    * @note エスケープシーケンスを使用してカーソルを指定位置に移動する。
 */
extern void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout); // 出力を即座に反映
}