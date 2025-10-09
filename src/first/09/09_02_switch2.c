#include <stdio.h>

int main() {
    char ch;
    
    printf("text? ");
    
    while ((ch = getchar()) != '\n') {
        switch (ch) {
            case ' ':
                printf("\n");
                break;
            default:
                putchar(ch);
                break;
        }
    }
    
    printf("\n");
    return 0;
}
