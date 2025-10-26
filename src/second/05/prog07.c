#include <stdio.h>
#include <string.h>

int swap_str(char *a, char *b) {
    char temp[128];

    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);

    return 0;
}

int main() {
    char a[128] = "abcde";
    char b[128] = "xyz";

    printf("a = %s, b = %s\n", a, b);
    swap_str(a, b);
    printf("swap!!!!!!!\n");
    printf("a = %s, b = %s\n", a, b);
    
    return 0;
}
