#include <stdio.h>

int main() {
    int a, b;
    printf("a? ");
    scanf("%d", &a);
    printf("b? ");
    scanf("%d", &b);
    
    if(a>0) {
        if(b==0) {
            printf("A\n");
        }
        else if(b>0) {
            printf("B\n");
        }
        else {
            printf("C\n");
        }
    }
    else {
        printf("D\n");
    }

}