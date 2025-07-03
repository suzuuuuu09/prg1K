#include <stdio.h>

int addOf(int a, int b) {
  printf("%d + %d = %d\n", a, b, a + b);
  return -1;
}

int main(int argc, const char* argv[]) {
  // 宣言, 変数は必ず初期化を行う
  int a = 5, b = 10, result = 0;
  //  関数の実行 & 出力
  addOf(a, b);
  return 0;
}
