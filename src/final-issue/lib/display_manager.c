#include <stdio.h>

#include "./utils.c"

// 文字をn秒おきに一行ずつ表示するアニメーション
void print_lines_interval(const char *text, float interval) {
    char *text_copy = strdup(text); // 元の文字列を変更しないようにコピー
    char *line = strtok(text_copy, "\n");
    
    while (line != NULL) {
        printf("%s\n", line);
        fflush(stdout);
        sleep_seconds(interval);  // 出力を即座に反映
        line = strtok(NULL, "\n");
    }
    
    free(text_copy); // メモリ解放
}

// 文字をn秒おきに一文字ずつ表示するアニメーション(タイプライター風)
void print_interval(char* text, float interval) {
    size_t text_length = strlen(text);
    for (size_t i = 0; i < text_length; i++) {
        putchar(text[i]);
        fflush(stdout); // 出力を即座に反映
        sleep_seconds(interval);
    }
}

// ロゴを表示
void display_logo() {
    print_lines_interval(LOGO, 0.3);
}

// 入力を取得
void get_input(char *prompt, char *buffer, int buffer_size) {
    print_interval(prompt, 0.05);
    fgets(buffer, buffer_size, stdin);
    
    // 改行文字を削除
    int len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

