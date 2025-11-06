#include <stdio.h>

int main() {
    char* str1 = "hoge";
    char* str2 = "hoge";

    if(str1 == str2) {
        printf("SAME");
    } else {
        printf("DIFF");
    }

    return 0;
}
