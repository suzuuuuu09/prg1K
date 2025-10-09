CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
TARGET = termiplay
SOURCE = 15_issue_k25012.c

# デフォルトターゲット
all: $(TARGET)

# 実行ファイルをビルド
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

# homebrewでffmpegをインストール
install-ffmpeg:
	@echo "Checking if Homebrew is installed..."
	@which brew > /dev/null || (echo "Homebrew is not installed. Installing Homebrew..." && /bin/bash -c "$$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)")
	@echo "Installing ffmpeg via Homebrew..."
	brew install ffmpeg
	@echo "ffmpeg installation completed!"
	@echo "Verifying installation..."
	@ffmpeg -version | head -1
	@ffprobe -version | head -1

# ffmpegのインストール状況を確認
check-ffmpeg:
	@echo "Checking ffmpeg installation..."
	@if command -v ffmpeg >/dev/null 2>&1; then \
		echo "✓ ffmpeg is installed at: $$(which ffmpeg)"; \
		ffmpeg -version | head -1; \
	else \
		echo "✗ ffmpeg is not installed"; \
		echo "Run 'make install-ffmpeg' to install it"; \
	fi
	@if command -v ffprobe >/dev/null 2>&1; then \
		echo "✓ ffprobe is installed at: $$(which ffprobe)"; \
		ffprobe -version | head -1; \
	else \
		echo "✗ ffprobe is not installed"; \
		echo "Run 'make install-ffmpeg' to install it"; \
	fi

# セットアップ（依存関係の確認とインストール）
setup: check-ffmpeg
	@if ! command -v ffmpeg >/dev/null 2>&1; then \
		echo "ffmpeg is not found. Installing..."; \
		$(MAKE) install-ffmpeg; \
	else \
		echo "All dependencies are satisfied!"; \
	fi

# クリーンアップ
clean:
	rm -f $(TARGET)
	rm -f /tmp/video_frames.raw

.PHONY: all clean setup install-ffmpeg check-ffmpeg