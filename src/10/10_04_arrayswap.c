#include <stdio.h>

int main() {
  int a[5] = {1, 2, 3, 4, 5};
  int x, y;
  int temp;

  printf("何番目を入れ替えますか? ");
  scanf("%d %d", &x, &y);

  if(x < 1 || x > 5 || y < 1 || y > 5) {
    printf("正しくありません\n");
  }
  else {
    temp = a[x - 1];
    a[x - 1] = a[y - 1];
    a[y - 1] = temp;

    for (int i = 0; i < 5; i++) {
      printf("a[%d]=%d \n", i, a[i]);
    }
  }

  return 0;
}
