#include <stdio.h>

int main() {
    int index = -1;
    char searchTerm[13] = {"\0"};
    char paragraph[] =
        "we hold these truths to be self-evident, that all men are created "
        "equal, that they are endowed by their creator with certain unalienable "
        "rights, that among these are life, liberty and the pursuit of "
        "happiness.";
    
    printf("searchTerm: ");
    scanf("%12s", searchTerm);
    
    for(int i = 0; paragraph[i] != '\0'; i++) {
        int j = 0;
        while (searchTerm[j] != '\0' && paragraph[i + j] == searchTerm[j]) {
            j++;
        }
        if (searchTerm[j] == '\0') {
            index = i;
            break;
        }
    }

    printf("indexOf: %d\n", index);

    return 0;
}