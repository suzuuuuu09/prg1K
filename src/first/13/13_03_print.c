#include <stdio.h>
void printFunc(void);

int main(int argc, const char* argv[]) {
  printFunc();
  return 0;
}

void printFunc(void) {
    for(int i = 1; i <= 5; i++) {
        printf("%d\n", i);
    }
}