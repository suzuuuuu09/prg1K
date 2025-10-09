#include <stdio.h>

int subOf(int a, int b) {
  return a - b;
}

int main(int argc, const char* argv[]) {
  // 宣言, 変数は必ず初期化を行う
  int a = 5, b = 10, result = 0;
  //  関数の実行
  result = subOf(a, b);
  // 出力
  printf("%d - %d = %d\n", a, b, result);
  return 0;
}
