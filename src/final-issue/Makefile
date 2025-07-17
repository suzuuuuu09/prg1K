CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./lib/ffmpeg-build/include
LDFLAGS = -L./lib/ffmpeg-build/lib -lavcodec -lavformat -lavutil -lswscale -lm
TARGET = termiplay
SOURCE = 15_k25012_issues.c

# デフォルトターゲット
all: $(TARGET)

# 実行ファイルをビルド
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

# クリーンアップ
clean:
	rm -f $(TARGET)
	rm -f /tmp/video_frames.raw

.PHONY: all clean