#include <stdio.h>

int setBit8(unsigned char bits, int i);
int resetBit8(unsigned char bits, int i);
int printbin8(unsigned char x);

int main() {
  unsigned char bits = 123; // (123)_10 = (0 1 1 1 1 0 1 1)_2
  bits = resetBit8(setBit8(bits, 7), 3);

  printbin8(bits); // 「1 1 1 1 0 0 1 1」と表示されれば OK

  return 0;
}
