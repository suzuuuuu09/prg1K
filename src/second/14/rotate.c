#include <stdio.h>

#define BIT_MASK 0xFF

unsigned int x = 0;
int n = 0;

// 整数 x を n ビット右回転させる関数
unsigned int rrotate(unsigned int x, int n) {
  x = x & BIT_MASK; // 8ビットでマスク
  return ((x >> n) | (x << (8 - n))) & BIT_MASK;
}

// 整数 x を n ビット左回転させる関数
unsigned int lrotate(unsigned int x, int n) {
  x = x & BIT_MASK; // 8ビットでマスク
  return ((x << n) | (x >> (8 - n))) & BIT_MASK;
}

// シフトを使って2進数を表示
unsigned int printbin(unsigned int x) {
  if (x == 0) return 0;

  printbin(x >> 1);
  printf("%d", x & 1);

  return 0;
}

int main() {
  printf("x: ");
  scanf("%d", &x);
  printf("n: ");
  scanf("%d", &n);

  printf("Q1: ");
  printbin(rrotate(x, n));
  printf("\n");
  printf("Q2: ");
  printbin(lrotate(x, n));
  printf("\n");

  return 0;
}
