#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <sys/select.h>

#include "./consts.c"
#include "./display_manager.c"
#include "./animation.c"
#include "./terminal.c"
#include "./types.c"

#define DEFAULT_FPS 30.0f
#define CHAR_ASPECT_RATIO 0.55f
#define MIN_DISPLAY_WIDTH 20
#define MIN_DISPLAY_HEIGHT 10
#define TERMINAL_MARGIN_WIDTH 4
#define TERMINAL_MARGIN_HEIGHT 6
#define MAX_DISPLAY_WIDTH 160
#define RGB_CHANNELS 3
#define NANOSECONDS_PER_SECOND 1000000000L
#define NANOSECONDS_PER_MICROSECOND 1000L
#define TEMP_FRAME_FILE "/tmp/video_frames.raw"


/*
 * @brief 動画の情報(幅，高さ，フレームレート)を取得する
 * @param video_path 動画ファイルのパス
 * @param info 動画の情報を入れるポインタ
*/
void get_video_info(const char *video_path, VideoInfo *info) {
    char command[1024];
    
    // ffprobeで動画の幅，高さ，フレームレートを取得する
    snprintf(command, sizeof(command),
        "ffprobe -v quiet -print_format csv=p=0 -show_entries stream=width,height,r_frame_rate \"%s\"",
        video_path);
    
    FILE *pipe = popen(command, "r");

    if(!pipe) return;

    // データを取得できたら
    char line[256];
    if (fgets(line, sizeof(line), pipe)) {
        char fps_str[32];
        sscanf(line, "%d,%d,%s", &info->width, &info->height, fps_str);

        // フレームレートの文字列から数値に変換する ("30/1" -> 30.0f)
        int num, den;
        info->fps = (sscanf(fps_str, "%d/%d", &num, &den) == 2) ?
                    (float)num / den : DEFAULT_FPS;
    }
    pclose(pipe);  // 閉じる
}

/*
 * @brief 動画の表示サイズを計算する
 * @param term_width ターミナルの幅
 * @param term_height ターミナルの高さ
 * @param video_info 動画の情報(幅，高さ，フレームレート)
 * @param display_size 表示サイズを入れるポインタ
*/
void calculate_display_size(int term_width, int term_height, const VideoInfo *video_info, DisplaySize *display_size) {
    // 利用可能なスペース
    int available_width = term_width - TERMINAL_MARGIN_WIDTH;
    int available_height = term_height - TERMINAL_MARGIN_HEIGHT;
    
    // 元の動画のアスペクト比
    float video_aspect = (float)video_info->width / video_info->height;
    const int fixed_width = (term_width > MAX_DISPLAY_WIDTH) ? MAX_DISPLAY_WIDTH : available_width;
    
    // 固定幅に基づいて高さを計算
    int calculated_height = (int)(fixed_width / video_aspect * CHAR_ASPECT_RATIO);
    
    // ターミナルサイズ内に収まるように調整
    if (calculated_height > available_height) {
        calculated_height = available_height;
        display_size->width = (int)(calculated_height * video_aspect / CHAR_ASPECT_RATIO);
    } else {
        display_size->width = fixed_width;
    }
    
    display_size->height = calculated_height;
    
    // 表示サイズが最小サイズ以下にならないようにする
    if (display_size->width < MIN_DISPLAY_WIDTH) display_size->width = MIN_DISPLAY_WIDTH;
    if (display_size->height < MIN_DISPLAY_HEIGHT) display_size->height = MIN_DISPLAY_HEIGHT;
}

/*
 * @brief 現在の時刻を取得する
 * @return 現在の時刻を表すtimespec構造体
 * @note システムの起動後の経過時間を取得する
*/
struct timespec get_current_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts;
}

/*
 * @brief 時間の差をマイクロ秒単位で計算する
 * @param start 開始時刻
 * @param end 終了時刻
 * @return 開始から終了までの時間差（マイクロ秒）
*/
long timespec_diff_us(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * MICROSECONDS_PER_SECOND + (end.tv_nsec - start.tv_nsec) / 1000L;
}

/*
 * @brief 時間の差をマイクロ秒単位で計算する
 * @param start 開始時刻
 * @param end 終了時刻
 * @return 開始から終了までの時間差（マイクロ秒）
*/
struct timespec calculate_next_frame_time(struct timespec current_time, long frame_interval_us) {
    current_time.tv_nsec += frame_interval_us * NANOSECONDS_PER_MICROSECOND;
    if (current_time.tv_nsec >= NANOSECONDS_PER_SECOND) {
        current_time.tv_sec += 1;
        current_time.tv_nsec -= NANOSECONDS_PER_SECOND;
    }
    return current_time;
}

/*
 * @brief フレームを一行表示する
 * @param frame_buffer フレームデータのバッファ
 * @param y 行番号
 * @param display_size 表示サイズ
 * @param offset_x X座標オフセット
 * @param offset_y Y座標オフセット
*/
void display_frame_row(unsigned char *frame_buffer, int y, const DisplaySize *display_size,
                      int offset_x, int offset_y) {
    printf("\033[%d;%dH", offset_y + y + 1, offset_x + 1);
    
    for (int x = 0; x < display_size->width; x++) {
        int pixel_idx = (y * display_size->width + x) * RGB_CHANNELS;
        size_t frame_size = (size_t)(display_size->width * display_size->height * RGB_CHANNELS);
        
        if (pixel_idx + 2 < (int)frame_size) {
            unsigned char r = frame_buffer[pixel_idx];
            unsigned char g = frame_buffer[pixel_idx + 1];
            unsigned char b = frame_buffer[pixel_idx + 2];
            
            print_colored_block(r, g, b);
        }
    }
}

/*
 * @brief 単一フレームを表示する
 * @param frame_buffer フレームデータ
 * @param display_size 表示サイズ
 * @param offset_x X座標オフセット
 * @param offset_y Y座標オフセット
 */
void display_frame(unsigned char *frame_buffer, const DisplaySize *display_size, 
                  int offset_x, int offset_y) {
    clear_screen();
    
    // フレームを高速表示
    for (int y = 0; y < display_size->height; y++) {
        display_frame_row(frame_buffer, y, display_size, offset_x, offset_y);
    }
    
    // 色をリセット
    reset_color();
    fflush(stdout);
}

/*
 * @brief 動画のフレームファイルを作成する
 * @param video_path 動画ファイルのパス
 * @param display_size 表示サイズ
 * @param fps フレームレート
 * @return 成功した場合は0、失敗した場合は-1
 */
int create_frame_file(const char *video_path, const DisplaySize *display_size, float fps) {
    char command[1024];
    snprintf(command, sizeof(command), 
        "ffmpeg -i \"%s\" -vf \"scale=%d:%d:flags=lanczos\" -r %.1f -f rawvideo -pix_fmt rgb24 -y " TEMP_FRAME_FILE " 2>/dev/null",
        video_path, display_size->width, display_size->height, fps);
    
    printf("Processing video...\n");
    int result = system(command);
    return (result == 0) ? 0 : -1;
}

/*
 * @brief フレーム表示のタイミング制御
 * @param next_frame_time 次のフレーム表示時刻
 */
void control_frame_timing(struct timespec next_frame_time) {
    struct timespec current_time = get_current_time();
    long sleep_time_us = timespec_diff_us(current_time, next_frame_time);
    
    if (sleep_time_us > 0 && sleep_time_us < 1000000) {
        usleep(sleep_time_us);
    }
}

/*
 * @brief 動画再生の初期化処理
 * @param video_path 動画ファイルのパス
 * @param video_info 動画情報
 * @param display_size 表示サイズ
 * @return 成功した場合は0、失敗した場合は-1
 */
int initialize_video_playback(const char *video_path, VideoInfo *video_info, DisplaySize *display_size) {
    int term_width, term_height;
    
    get_terminal_size(&term_width, &term_height);
    
    // 動画の情報を取得
    printf("Retrieving video information...\n");
    get_video_info(video_path, video_info);
    
    if (video_info->width == 0 || video_info->height == 0) {
        printf("The information on the video could not be retrieved. Please try again.\n");
        return -1;
    }
    
    // 表示サイズを計算
    calculate_display_size(term_width, term_height, video_info, display_size);
    
    return 0;
}

/*
 * @brief 動画再生のクリーンアップ処理
 * @param frames_file フレームファイルポインタ
 * @param frame_buffer フレームバッファ
 */
void cleanup_video_playback(FILE *frames_file, unsigned char *frame_buffer) {
    disable_raw_mode();
    show_cursor();
    exit_fullscreen();
    
    if (frames_file) fclose(frames_file);
    if (frame_buffer) free(frame_buffer);
    
    // 一時ファイルを削除
    remove(TEMP_FRAME_FILE);
}

/*
 * @brief 動画ファイルパスの入力処理
 * @param video_path パスを格納するバッファ
 * @param buffer_size バッファサイズ
 */
void input_video_path(char *video_path, size_t buffer_size) {
    do {
        get_input("Please enter the path of the video: ", video_path, buffer_size);
        
        if (!file_exists(video_path)) {
            print_interval("Video File is not found.\n", 0.05);
            sleep_seconds(1.0);
        }
    } while (!file_exists(video_path));
}

/*
 * @brief 最適化された動画再生関数
 * @param video_path 動画ファイルのパス
 * @note 動画のフレームをターミナルに表示する
 *       高速なフレーム表示と正確なタイミング制御を行う
*/
void play_video(const char *video_path) {
    VideoInfo video_info = {0};
    DisplaySize display_size = {0};
    
    // 初期化処理
    initialize_video_playback(video_path, &video_info, &display_size);
    
    // フレームファイルの作成
    if (create_frame_file(video_path, &display_size, video_info.fps) != 0) {
        printf("Video processing failed. Please try again.\n");
        return;
    }
    
    // フレームファイルを開く
    FILE *frames_file = fopen(TEMP_FRAME_FILE, "rb");
    if (!frames_file) {
        printf("Could not open frame file. Please try again.\n");
        return;
    }
    
    // フレームサイズを計算
    size_t frame_size = (size_t)(display_size.width * display_size.height * RGB_CHANNELS);
    unsigned char *frame_buffer = malloc(frame_size);
    
    if (!frame_buffer) {
        printf("Memory allocation failed. Please try again.\n");
        cleanup_video_playback(frames_file, NULL);
        return;
    }
    
    enter_fullscreen();
    hide_cursor();
    enable_raw_mode();
    
    printf("Playing video...\n");
    sleep_seconds(1.0);
    
    // フレーム間隔をマイクロ秒で計算
    long frame_interval_us = (long)(1000000.0 / video_info.fps);
    
    // 画面の中央に配置するためのオフセット
    int term_width, term_height;
    get_terminal_size(&term_width, &term_height);
    int offset_x = (term_width - display_size.width) / 2;
    int offset_y = (term_height - display_size.height) / 2;
    
    // タイマー初期化
    struct timespec next_frame_time = get_current_time();
    size_t bytes_read;
    
    while ((bytes_read = fread(frame_buffer, 1, frame_size, frames_file)) == frame_size) {
        // フレーム表示タイミングを計算
        next_frame_time = calculate_next_frame_time(next_frame_time, frame_interval_us);
        
        // フレームを表示
        display_frame(frame_buffer, &display_size, offset_x, offset_y);
        
        // 正確なフレームタイミングで待機
        control_frame_timing(next_frame_time);
    }
    
    cleanup_video_playback(frames_file, frame_buffer);
}
