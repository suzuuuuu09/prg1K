#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>

// ターミナルの設定を保存する構造体
struct termios orig_termios;

// シグナルハンドラー
void signal_handler(int sig) {
    (void)sig; // 未使用パラメータ警告を抑制
    printf("\n\033[0m\033[?25h"); // 色をリセット、カーソルを表示
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    exit(0);
}

// RawModeを有効化する
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    signal(SIGINT, signal_handler);
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// RawModeを無効化する
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// ターミナルのサイズを取得
void get_terminal_size(int *width, int *height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}

// RGBの値を元に色のブロックを表示する
void print_colored_block(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm█", r, g, b);
}