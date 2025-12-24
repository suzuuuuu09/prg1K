#include <stdio.h>

#define DEBUG_MSG

int main() {
#ifdef DEBUG_MSG
    printf("Hello world!\n");
#endif
    return 0;
}
