#include <stdio.h>
#include <opencv2/opencv.hpp>

extern "C" {
    int video() {
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

    int main() {
        video();
    }
}