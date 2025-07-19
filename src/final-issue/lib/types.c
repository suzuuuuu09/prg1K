#pragma once

// 動画の情報
typedef struct {
    int width;
    int height;
    float fps;
} VideoInfo;

// ターミナル内で表示する動画のサイズ
typedef struct {
    int width;
    int height;
} DisplaySize;