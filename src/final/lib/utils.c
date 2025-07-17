#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MICROSECONDS_PER_SECOND 1000000

// 端末設定を保存するためのグローバル変数
struct termios original_termios;

/**
 * @brief raw modeの有効/無効を切り替える関数
 * @param enable
 * @note 入力をリアルタイムで取得するモードに移行
 */
extern void raw_mode(bool enable) {
    if (enable) {
        // raw modeを有効にする
        if (tcgetattr(STDIN_FILENO, &original_termios) == -1) {
            perror("tcgetattr");
            return;
        }
        
        struct termios raw = original_termios;
        raw.c_lflag &= ~(ECHO | ICANON);  // エコーとカノニカルモードを無効化
        raw.c_cc[VMIN] = 1;
        raw.c_cc[VTIME] = 0;
        
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
            perror("tcsetattr");
            return;
        }
    } else if (!enable) {
        // raw modeを無効にする
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1) {
            perror("tcsetattr");
            return;
        }
    }
}

/**
 * @brief 文字数制限付きで文字列を入力する関数
 * @param buffer 入力を格納するバッファ
 * @param max_length 最大文字数
 */
extern void input_limit(char* buffer, int max_length) {
    int i = 0;
    char ch;
    
    fflush(stdout);
    
    // 非カノニカルモードを有効化
    raw_mode(true);
    
    while (1) {
        ch = getchar();
        
        if (ch == '\n' || ch == '\r') {  // Enterキーで終了
            break;
        } else if (ch == 127 || ch == 8) {  // バックスペースの処理
            if (i > 0) {
                i--;
                printf("\b \b");  // カーソルを戻して文字を削除
                fflush(stdout);
            }
        } else if (ch >= 32 && ch <= 126) {  // 印刷可能文字のみ
            if (i < max_length) {  // 最大文字数未満の場合のみ文字を追加
                buffer[i] = ch;
                putchar(ch);  // 入力された文字を表示
                fflush(stdout);
                i++;
            }
            // 最大文字数に達している場合は完全に無視（キーが効かない）
        }
    }
    
    buffer[i] = '\0';  // null終端文字を追加
    printf("\n");
    
    // 通常の入力モードに戻す
    raw_mode(false);
}

/**
 * @brief 引数のテキストが何行あるか数える関数
 * @param text 対象の文字列
 * @return 行数
 */
extern int count_text_line(char* text) {
    int line_count = 1;
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

/**
 * @brief n秒間処理を一時停止する関数
 * @param seconds 停止時間（秒）
 */
extern void sleep_seconds(float seconds) {
    usleep((int)(seconds * MICROSECONDS_PER_SECOND)); // 秒をマイクロ秒に変換
}

/**
 * @brief 配列をシャッフルする関数（Fisher-Yates shuffle）
 * @param array シャッフルする配列
 * @param size 配列のサイズ
 */
extern void shuffle_array(void* array, size_t size, size_t element_size) {
    char* arr = (char*)array;
    char* temp = malloc(element_size);
    
    for (size_t i = size - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        
        // arr[i]とarr[j]を交換
        memcpy(temp, arr + i * element_size, element_size);
        memcpy(arr + i * element_size, arr + j * element_size, element_size);
        memcpy(arr + j * element_size, temp, element_size);
    }
    
    free(temp);
}

/**
 * @brief 1から指定された最大値までの数字を入力させる関数
 * @param max 最大値
 * @return 入力された数字
 */
extern int input_number(int max) {
    char buffer[10];
    int number;
    
    while (1) {
        printf("1-%dの数字を入力してください: ", max);
        input_limit(buffer, 2);
        
        number = atoi(buffer);
        if (number >= 1 && number <= max) {
            return number;
        }
        
        printf("無効な入力です。\n");
    }
}

/**
 * @brief 矢印キーでの選択機能
 * @param options 選択肢の配列
 * @param count 選択肢の数
 * @param prompt 表示するプロンプト
 * @return 選択されたインデックス
 */
extern int select_with_arrow_keys(char** options, int count, const char* prompt) {
    int selected = 0;
    char ch;
    
    raw_mode(true);
    
    while (1) {
        // 画面をクリアして選択肢を表示
        clear_screen();
        printf("%s\n\n", prompt);
        
        for (int i = 0; i < count; i++) {
            if (i == selected) {
                printf("-> %s\n", options[i]);
            } else {
                printf("   %s\n", options[i]);
            }
        }
        
        printf("\n矢印キーで選択、Enterで決定");
        fflush(stdout);
        
        ch = getchar();
        
        if (ch == 27) { // ESCシーケンス
            getchar(); // '['
            ch = getchar(); // 方向キー
            
            switch (ch) {
                case 'A': // 上矢印
                    selected = (selected - 1 + count) % count;
                    break;
                case 'B': // 下矢印
                    selected = (selected + 1) % count;
                    break;
            }
        } else if (ch == '\n' || ch == '\r') { // Enter
            break;
        }
    }
    
    raw_mode(false);
    return selected;
}
