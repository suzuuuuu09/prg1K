CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = video_player
SOURCE = 15_k25012_issues.c

# デフォルトターゲット
all: $(TARGET)

# 実行ファイルをビルド
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# クリーンアップ
clean:
	rm -f $(TARGET)
	rm -f /tmp/video_frames.raw

# テスト実行（サンプル動画で）
test: $(TARGET)
	./$(TARGET)

# インストール（オプション）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# アンインストール
uninstall:
	rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean test install uninstall