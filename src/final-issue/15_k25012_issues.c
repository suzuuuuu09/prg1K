#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <time.h>

// ターミナルの設定を保存する構造体
struct termios orig_termios;

// シグナルハンドラー
void signal_handler(int sig) {
    printf("\n\033[0m\033[?25h"); // 色をリセット、カーソルを表示
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    exit(0);
}

// ターミナルの設定を変更（cbreak mode）
void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    signal(SIGINT, signal_handler);
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// ターミナルの設定を元に戻す
void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

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

// ターミナルのサイズを取得
void get_terminal_size(int *width, int *height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}

// RGB値からANSIカラーコードを生成
void print_colored_block(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm█", r, g, b);
}

// 文字を一文字ずつ表示するアニメーション
void print_with_interval(const char *text, float interval) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        putchar(text[i]);
        fflush(stdout);
        usleep((useconds_t)(interval * 1000000));
    }
}

// 行ごとにアニメーション表示
void print_lines_with_interval(const char *text, float interval) {
    char *text_copy = strdup(text);
    char *line = strtok(text_copy, "\n");
    
    while (line != NULL) {
        printf("%s\n", line);
        fflush(stdout);
        usleep((useconds_t)(interval * 1000000));
        line = strtok(NULL, "\n");
    }
    
    free(text_copy);
}

// ロゴを表示
void display_logo() {
    const char *logo = 
        " _                           _                _                _      _                             _\n"
        "| |_   ___  _ __  _ __ ___  (_) _ __    __ _ | |       __   __(_)  __| |  ___   ___          _ __  | |  __ _  _   _   ___  _ __ \n"
        "| __| / _ \\| '__|| '_ ` _ \\ | || '_ \\  / _` || | _____ \\ \\ / /| | / _` | / _ \\ / _ \\  _____ | '_ \\ | | / _` || | | | / _ \\| '__|\n"
        "| |_ |  __/| |   | | | | | || || | | || (_| || ||_____| \\ V / | || (_| ||  __/| (_) ||_____|| |_) || || (_| || |_| ||  __/| |   \n"
        " \\__| \\___||_|   |_| |_| |_||_||_| |_| \\__,_||_|         \\_/  |_| \\__,_| \\___| \\___/        | .__/ |_| \\__,_| \\__, | \\___||_|   \n"
        "                                                                                            |_|               |___/\n";
    
    print_lines_with_interval(logo, 0.3);
}

// ローディングアニメーション
void loading_animation(float duration) {
    const char *spinner = "|/-\\";
    int spinner_len = 4;
    int iterations = (int)(duration * 10); // 0.1秒間隔で回転
    
    printf("読み込み中 ");
    for (int i = 0; i < iterations; i++) {
        printf("\b%c", spinner[i % spinner_len]);
        fflush(stdout);
        usleep(100000); // 0.1秒
    }
    printf("\b完了!\n");
}

// 動画を再生する関数
void play_video(const char *video_path) {
    int width, height;
    get_terminal_size(&width, &height);
    
    // ffmpegコマンドを構築
    char command[1024];
    snprintf(command, sizeof(command), 
        "ffmpeg -i \"%s\" -vf \"scale=%d:%d,fps=30\" -f rawvideo -pix_fmt rgb24 -y /tmp/video_frames.raw 2>/dev/null",
        video_path, width, height-2);
    
    printf("動画を処理中...\n");
    int result = system(command);
    if (result != 0) {
        printf("エラー: 動画の処理に失敗しました。\n");
        return;
    }
    
    FILE *frames_file = fopen("/tmp/video_frames.raw", "rb");
    if (!frames_file) {
        printf("エラー: フレームファイルを開けません。\n");
        return;
    }
    
    // フレームサイズを計算
    int frame_size = width * height * 3; // RGB24
    unsigned char *frame_buffer = malloc(frame_size);
    
    enter_fullscreen();
    hide_cursor();
    enable_raw_mode();
    
    printf("動画を再生中... (qで終了)\n");
    sleep(2);
    
    while (fread(frame_buffer, 1, frame_size, frames_file) == frame_size) {
        clear_screen();
        cursor_move(1, 1);
        
        // フレームを表示
        for (int y = 0; y < height-2; y++) {
            for (int x = 0; x < width; x++) {
                int pixel_idx = (y * width + x) * 3;
                int r = frame_buffer[pixel_idx];
                int g = frame_buffer[pixel_idx + 1];
                int b = frame_buffer[pixel_idx + 2];
                print_colored_block(r, g, b);
            }
            printf("\033[0m\n"); // 色をリセットして改行
        }
        
        fflush(stdout);
        usleep(33333); // 約30FPS (1/30秒)
        
        // 'q'キーが押されたかチェック
        fd_set readfds;
        struct timeval timeout;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        
        if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0) {
            char ch = getchar();
            if (ch == 'q' || ch == 'Q') {
                break;
            }
        }
    }
    
    disable_raw_mode();
    show_cursor();
    exit_fullscreen();
    
    fclose(frames_file);
    free(frame_buffer);
    
    // 一時ファイルを削除
    remove("/tmp/video_frames.raw");
    
    printf("再生が完了しました。\n");
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

// 入力を取得
void get_input(const char *prompt, char *buffer, int buffer_size) {
    print_with_interval(prompt, 0.05);
    fgets(buffer, buffer_size, stdin);
    
    // 改行文字を削除
    int len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

int main() {
    char video_path[256];
    
    clear_screen();
    cursor_move(1, 1);
    
    // ロゴを表示
    display_logo();
    
    cursor_move(1, 9);
    
    // 動画ファイルのパスを取得
    do {
        get_input("再生したい動画のパスを入力してください: ", video_path, sizeof(video_path));
        
        if (!file_exists(video_path)) {
            printf("エラー: ファイルが見つかりません。\n");
        }
    } while (!file_exists(video_path));
    
    // ローディングアニメーション
    loading_animation(2.0);
    
    // 動画を再生
    play_video(video_path);
    
    return 0;
}