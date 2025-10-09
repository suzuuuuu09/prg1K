#include <stdio.h>

// bits の下から i ビット目 (範囲は 0～7 ビット目) を 1 にする
int setBit8(unsigned char bits, int i) {
  return bits | (1 << i);
}

// bits の下から i ビット目 (範囲は 0～7 ビット目) を 0 にする
int resetBit8(unsigned char bits, int i) {
  return bits & ~(1 << i);
}

// 演習 (B-3) の 8 ビット版
int printbin8(unsigned char x) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
  printf("\n");

  return 0;
}
