#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "../opencv_interface.h"  // パスを修正

extern "C" {
    int video_get_resolution(void) {
        // video/badapple.mp4の画面サイズを取得
        cv::VideoCapture cap("video/badapple.mp4");
        if (!cap.isOpened()) {
            printf("動画を開けませんでした\n");
            return -1;
        }
        
        int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("動画の画面サイズ: %dx%d\n", frame_width, frame_height);
        
        cap.release();
        return 0;
    }
    
    int display_image_wrapper(const char* image_path) {
        // 画像を読み込み
        cv::Mat image = cv::imread(image_path);
        
        if (image.empty()) {
            printf("画像を読み込めませんでした: %s\n", image_path);
            return -1;
        }
        
        // ウィンドウを作成して画像を表示
        cv::namedWindow("OpenCV Example", cv::WINDOW_AUTOSIZE);
        cv::imshow("OpenCV Example", image);
        
        printf("キーを押すと終了します...\n");
        cv::waitKey(0);
        
        // ウィンドウを閉じる
        cv::destroyAllWindows();
        
        return 0;
    }
}