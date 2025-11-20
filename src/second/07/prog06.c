/* 問題6 */
/* • 文字列 */
/* char *str1="ABCDE"; */
/* char *str2="XYZ"; */
/* char *str; */
/* • ２つの文字列を連結した文字列strを作る */
/* • mallocを使うこと */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *str1 = "ABCDE";
    char *str2 = "XYZ";
    char *str;

    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);
    str = (char *)malloc((str1_len + str2_len + 1) * sizeof(char));
    if(str == NULL){
        printf("No enough memory.\n");
        exit(1);
    }
    strcpy(str, str1);
    strcat(str, str2);

    printf("str = %s\n", str);
    free(str); /* メモリ開放 */

    return 0;
}
