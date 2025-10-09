#include <stdio.h>

#include "lib/video.c"

int main() {
    char video_path[256];
    
    clear_screen();
    cursor_move(1, 1);
    
    // ロゴを表示
    display_logo();
    cursor_move(1, 11);
    
    // 動画ファイルのパスを入力
    input_video_path(video_path, sizeof(video_path));
    
    // ローディングアニメーション
    loading_animation(2.0);
    
    play_video(video_path);
    
    return 0;
}