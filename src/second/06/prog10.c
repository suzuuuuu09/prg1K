/* char str[128]="foo,bar,hoge,fuga"; */
/* コンマ区切りの⽂字列を，コンマで分割せよ． */

#include <stdio.h>
#include <string.h>

int main() {
    char str[128] = "foo,bar,hoge,fuga";
    char *token;

    token = strtok(str, ",");

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
