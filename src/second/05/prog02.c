#include <stdio.h>

int my_strlen(char *str) {
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

int main() {
  char str1[128] = "abc";
  char str2[] = "cde";
  char *str = "fgh";

  int length_str1 = my_strlen(str1);
  int length_str2 = my_strlen(str2);
  int length_str = my_strlen(str);

  printf("str1: length = %d\n", length_str1);
  printf("str2: length = %d\n", length_str2);
  printf("str: length = %d\n", length_str);

  return 0;
}
