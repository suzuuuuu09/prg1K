// ファイル名は「kadai1-main.c」とする
#include <stdio.h>
#include <stdlib.h>

void yomiage(long long n);

int main() {
  char ss[256];                 // 文字列は char の配列 (詳細は後日)
  long long n;                  // int よりも大きい整数値を扱える型
                                // (詳しくは 各自で 調べなさい)
  printf("Number ? ");

  fgets(ss, sizeof(ss), stdin); // 数値を文字列として入力し
  n = atoll(ss);                // さらに 数値に変換する処理のコード

  printf("%lld = ", n);         // long long 型の場合 「%d」ではなく
  yomiage(n);                   // 「%lld」とする (詳細は 各自調べよ)

  printf("\n");
  return 0;
}
