#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#include "./utils.c"
#include "./consts.c"

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
        sleep_seconds(interval);
    }
}

void sprint_interval(float interval, const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    print_interval(buffer, interval);
}

/**
 * @brief n秒おきに文字列を行ごとに表示する関数
 * @param text 表示する文字列
 * @param interval 表示間隔（秒）
*/
void print_interval_line(const char* text, float interval) {
    char* text_copy = strdup(text); // 元の文字列を変更しないようにコピー
    char* line = strtok(text_copy, "\n");
    
    while (line != NULL) {
        printf("%s\n", line);
        fflush(stdout); // 出力を即座に反映
        sleep_seconds(interval);
        line = strtok(NULL, "\n");
    }
    
    /* これないと何故か動かなくなる */
    free(text_copy); // メモリの解放
}