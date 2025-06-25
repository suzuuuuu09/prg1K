# 1. C++部分をコンパイル
g++ -c lib/opencv.cpp -o lib/opencv.o `pkg-config --cflags opencv4`

# 2. C部分をコンパイル
gcc -c text_displayer.c -o text_displayer.o

# 3. リンクして実行ファイル作成
g++ -o text_displayer_final text_displayer.o lib/opencv.o `pkg-config --libs opencv4`