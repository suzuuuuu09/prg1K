#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <sys/select.h>

#include "lib/consts.c"
#include "lib/text_displayer.c"
#include "lib/animation.c"

// ターミナルの設定を保存する構造体
struct termios orig_termios;

// シグナルハンドラー
void signal_handler(int sig) {
    (void)sig; // 未使用パラメータ警告を抑制
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

// ロゴを表示
void display_logo() {
    print_lines_with_interval(LOGO, 0.3);
}

// 動画の情報を取得する関数
void get_video_info(const char *video_path, int *orig_width, int *orig_height, float *fps) {
    char command[1024];
    FILE *pipe;
    
    // ローカルのffprobeを使用
    snprintf(command, sizeof(command), 
        "./lib/ffmpeg-build/bin/ffprobe -v quiet -print_format csv=p=0 -show_entries stream=width,height,r_frame_rate \"%s\"",
        video_path);
    
    pipe = popen(command, "r");
    if (pipe) {
        char line[256];
        if (fgets(line, sizeof(line), pipe)) {
            char fps_str[32];
            sscanf(line, "%d,%d,%s", orig_width, orig_height, fps_str);
            
            // フレームレートを計算 (例: "30/1" -> 30.0)
            int num, den;
            if (sscanf(fps_str, "%d/%d", &num, &den) == 2) {
                *fps = (float)num / den;
            } else {
                *fps = 30.0; // デフォルト
            }
        }
        pclose(pipe);
    }
}

// アスペクト比を保持して最適なサイズを計算
void calculate_display_size(int term_width, int term_height, int orig_width, int orig_height, 
                           int *display_width, int *display_height) {
    // ターミナルの文字のアスペクト比を正確に設定 (macOSでは約0.4-0.45が適切)
    const float char_aspect_ratio = 0.42; // 文字の実際の縦横比
    
    // 利用可能なスペース（余裕を持たせる）
    int available_width = term_width - 4;
    int available_height = term_height - 6;
    
    // 元の動画のアスペクト比
    float video_aspect = (float)orig_width / orig_height;
    
    // ターミナルで表示可能な実効アスペクト比
    float terminal_aspect = (float)available_width / available_height * char_aspect_ratio;
    
    // 動画のアスペクト比を厳密に維持して計算
    if (video_aspect > terminal_aspect) {
        // 横長動画：ターミナルの幅に合わせる
        *display_width = available_width;
        *display_height = (int)((float)available_width / video_aspect / char_aspect_ratio + 0.5);
        
        // 高さが利用可能範囲を超える場合は高さ基準で再計算
        if (*display_height > available_height) {
            *display_height = available_height;
            *display_width = (int)((float)available_height * video_aspect * char_aspect_ratio + 0.5);
        }
    } else {
        // 縦長または正方形動画：ターミナルの高さに合わせる
        *display_height = available_height;
        *display_width = (int)((float)available_height * video_aspect * char_aspect_ratio + 0.5);
        
        // 幅が利用可能範囲を超える場合は幅基準で再計算
        if (*display_width > available_width) {
            *display_width = available_width;
            *display_height = (int)((float)available_width / video_aspect / char_aspect_ratio + 0.5);
        }
    }
    
    // 最小・最大サイズを制限
    if (*display_width < 20) *display_width = 20;
    if (*display_height < 10) *display_height = 10;
    if (*display_width > available_width) *display_width = available_width;
    if (*display_height > available_height) *display_height = available_height;
    
    // 計算された表示アスペクト比を確認
    float calculated_aspect = (float)(*display_width) / (*display_height) * char_aspect_ratio;
    float aspect_error = fabs(calculated_aspect - video_aspect) / video_aspect * 100;
    
    if (aspect_error > 5.0) {
        printf("警告: アスペクト比の誤差が大きいです (%.2f%%)\n", aspect_error);
    }
}

// Pythonの実装を参考にしたアスペクト比維持関数
void calculate_display_size_python_style(int term_width, int term_height, 
                                        int orig_width, int orig_height, 
                                        int *display_width, int *display_height) {
    // Pythonと同じ固定幅アプローチを使用
    const int fixed_width = (term_width > 160) ? 160 : term_width - 4;
    
    // 元の動画のアスペクト比を計算
    float aspect_ratio = (float)orig_width / (float)orig_height;
    
    // Pythonと同じ補正係数（0.55）を使用
    const float terminal_char_correction = 0.55;
    
    // 固定幅に基づいて高さを計算
    int calculated_height = (int)(fixed_width / aspect_ratio * terminal_char_correction);
    
    // ターミナルサイズ内に収まるように調整
    int max_height = term_height - 6;
    if (calculated_height > max_height) {
        // 高さが制限を超える場合は高さ基準で再計算
        calculated_height = max_height;
        *display_width = (int)(calculated_height * aspect_ratio / terminal_char_correction);
    } else {
        *display_width = fixed_width;
    }
    
    *display_height = calculated_height;
    
    // 最小サイズを保証
    if (*display_width < 20) *display_width = 20;
    if (*display_height < 10) *display_height = 10;
}

// 動画を再生する関数
void play_video(const char *video_path) {
    int term_width, term_height;
    int orig_width, orig_height;
    int display_width, display_height;
    float fps;
    
    get_terminal_size(&term_width, &term_height);
    
    // 動画の情報を取得
    printf("動画情報を取得中...\n");
    get_video_info(video_path, &orig_width, &orig_height, &fps);
    
    if (orig_width == 0 || orig_height == 0) {
        printf("エラー: 動画の情報を取得できませんでした。\n");
        return;
    }
    
    // 表示サイズを計算（Pythonスタイルを使用）
    calculate_display_size_python_style(term_width, term_height, orig_width, orig_height, 
                          &display_width, &display_height);
    
    printf("元の解像度: %dx%d\n", orig_width, orig_height);
    printf("表示解像度: %dx%d\n", display_width, display_height);
    printf("FPS: %.1f\n", fps);
    
    // より正確なffmpegコマンドを構築（正確なサイズ指定）
    char command[1024];
    snprintf(command, sizeof(command), 
        "./lib/ffmpeg-build/bin/ffmpeg -i \"%s\" -vf \"scale=%d:%d:flags=lanczos,fps=%.1f\" -f rawvideo -pix_fmt rgb24 -y /tmp/video_frames.raw 2>/dev/null",
        video_path, display_width, display_height, fps);
    
    printf("実行するコマンド: %s\n", command);
    
    printf("動画を処理中...\n");
    int result = system(command);
    if (result != 0) {
        printf("エラー: 動画の処理に失敗しました。\n");
        return;
    }
    
    // 生成されたファイルのサイズを確認
    FILE *test_file = fopen("/tmp/video_frames.raw", "rb");
    if (test_file) {
        fseek(test_file, 0, SEEK_END);
        long file_size = ftell(test_file);
        fclose(test_file);
        printf("生成されたファイルサイズ: %ld bytes\n", file_size);
        printf("期待されるフレームサイズ: %ld bytes\n", (long)(display_width * display_height * 3));
        printf("フレーム数の推定: %.1f\n", (float)file_size / (display_width * display_height * 3));
    }
    
    FILE *frames_file = fopen("/tmp/video_frames.raw", "rb");
    if (!frames_file) {
        printf("エラー: フレームファイルを開けません。\n");
        return;
    }
    
    // フレームサイズを計算（型を合わせる）
    size_t frame_size = (size_t)(display_width * display_height * 3); // RGB24
    unsigned char *frame_buffer = malloc(frame_size);
    
    // 最初のフレームのデータを確認
    size_t bytes_read = fread(frame_buffer, 1, frame_size, frames_file);
    printf("最初のフレーム読み込み: %zu bytes (期待値: %zu)\n", bytes_read, frame_size);
    
    if (bytes_read == frame_size) {
        printf("最初の数ピクセルのRGB値:\n");
        for (int i = 0; i < 10 && i * 3 < (int)bytes_read; i++) {
            printf("ピクセル%d: R=%d G=%d B=%d\n", i, 
                   frame_buffer[i*3], frame_buffer[i*3+1], frame_buffer[i*3+2]);
        }
    }
    
    // ファイルの先頭に戻る
    fseek(frames_file, 0, SEEK_SET);
    
    enter_fullscreen();
    hide_cursor();
    enable_raw_mode();
    
    printf("動画を再生中... (qで終了)\n");
    sleep(2);
    
    // フレーム間隔を計算
    int frame_delay = (int)(1000000 / fps); // マイクロ秒
    
    // 画面の中央に配置するためのオフセット計算
    int offset_x = (term_width - display_width) / 2;
    int offset_y = (term_height - display_height) / 2;
    
    while (fread(frame_buffer, 1, frame_size, frames_file) == frame_size) {
        clear_screen();
        
        // フレームを中央に表示
        for (int y = 0; y < display_height; y++) {
            cursor_move(offset_x + 1, offset_y + y + 1);
            for (int x = 0; x < display_width; x++) {
                int pixel_idx = (y * display_width + x) * 3;
                int r = frame_buffer[pixel_idx];
                int g = frame_buffer[pixel_idx + 1];
                int b = frame_buffer[pixel_idx + 2];
                print_colored_block(r, g, b);
            }
            printf("\033[0m"); // 色をリセット
        }
        
        fflush(stdout);
        usleep(frame_delay);
        
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
void get_input(char *prompt, char *buffer, int buffer_size) {
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
    
    cursor_move(1, 11);
    
    // 動画ファイルのパスを取得
    do {
        get_input("Please enter the path of the video: ", video_path, sizeof(video_path));
        
        if (!file_exists(video_path)) {
            print_with_interval("Video File is not found.\n", 0.05);
            sleep_seconds(1.0f);
        }
    } while (!file_exists(video_path));
    
    // ローディングアニメーション
    loading_animation(2.0);
    
    // 動画を再生
    play_video(video_path);
    
    return 0;
}