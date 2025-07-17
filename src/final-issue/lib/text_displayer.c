#include <stdio.h>

#include "./utils.c"

// 文字をn秒おきに一行ずつ表示するアニメーション
void print_lines_with_interval(const char *text, float interval) {
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    
    while (line != NULL) {
        printf("%s\n", line);
        fflush(stdout);
        sleep_seconds(interval);  // 出力を即座に反映
        line = strtok(NULL, "\n");
    }
    
    free(text_copy);
}

// 文字をn秒おきに一文字ずつ表示するアニメーション
void print_with_interval(char* text, float interval) {
    size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++) {
        putchar(text[i]);
        fflush(stdout); // 出力を即座に反映
        sleep_seconds(interval);
    }
}