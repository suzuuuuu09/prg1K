#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./utils.c"
#include "opencv_interface.h"  // C++関数のインターフェース

#define MICROSECONDS_PER_SECOND 1000000

/**
    * @brief n秒おきに文字列を表示する関数
    * @param text 表示する文字列
    * @param interval 表示間隔（秒）
*/
void print_interval(char* text, float interval) {
    size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++) {
        putchar(text[i]);
        fflush(stdout); // 出力を即座に反映
        usleep((int)(interval * MICROSECONDS_PER_SECOND)); // 秒をマイクロ秒に変換してスリープ
    }
    printf("\n");
}

/**
    * @brief n秒おきに文字列を行ごとに表示する関数
    * @param text 表示する文字列
    * @param interval 表示間隔（秒）
*/
void print_interval_line(char* text, float interval) {
    // 行数を数える
    int line_count = count_text_line(text);
    
    // 1行ずつ表示
    char* line_start = text;
    for (int current_line = 0; current_line < line_count; current_line++) {
        // 現在行の終端を見つける
        char* line_end = strchr(line_start, '\n');
        
        if (line_end != NULL) {
            // 改行文字まで表示
            size_t line_length = line_end - line_start;
            for (size_t i = 0; i < line_length; i++) {
                putchar(line_start[i]);
            }
            putchar('\n'); // 改行文字も表示
            line_start = line_end + 1; // 次の行の開始位置
        } else {
            // 最後の行（改行文字がない場合）
            printf("%s", line_start);
            if (line_start[strlen(line_start) - 1] != '\n') {
                putchar('\n');
            }
        }
        
        fflush(stdout);
        usleep((int)(interval * MICROSECONDS_PER_SECOND)); // 行間隔でスリープ
    }
}

int main() {
    clear_screen();
    print_interval("Hello! My name is suzuuuuu09.", 0.08f);
    char logo[] =
    "████████╗███████╗██████╗ ███╗   ███╗██╗██████╗ ██╗      █████╗ ██╗   ██╗\n"
    "╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝\n"
    "   ██║   █████╗  ██████╔╝██╔████╔██║██║██████╔╝██║     ███████║ ╚████╔╝ \n"
    "   ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██╔═══╝ ██║     ██╔══██║  ╚██╔╝  \n"
    "   ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║     ███████╗██║  ██║   ██║   \n"
    "   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   \n";
    print_interval_line(logo, 0.5f);
    
    // C++で実装されたvideo関数を呼び出し
    printf("\n=== OpenCV video関数の実行 ===\n");
    video_get_resolution();
    
    return 0;
}