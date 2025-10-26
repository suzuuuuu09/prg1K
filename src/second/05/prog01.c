#include <stdio.h>
#include <string.h>

int main() {
  char str1[128] = "abc";
  char str2[] = "cde";
  char *str = "fgh";

  size_t length_str1 = strlen(str1);
  size_t length_str2 = strlen(str2);
  size_t length_str = strlen(str);

  size_t size_str1 = sizeof(str1);
  size_t size_str2 = sizeof(str2);
  size_t size_str = sizeof(str);

  printf("str1: length = %zu, size = %zu\n", length_str1, size_str1);
  printf("str2: length = %zu, size = %zu\n", length_str2, size_str2);
  printf("str: length = %zu, size = %zu\n", length_str, size_str);

  return 0;
}
