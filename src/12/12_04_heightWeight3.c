#include <stdio.h>

int main() {
  int human[3][2] = {0};

  for(int i = 0; i < 3; i++) {
    printf("%d人目の身長と体重? ", i + 1);
    scanf("%d %d", &human[i][0], &human[i][1]);
  }

  for (int i = 0; i < 3; i++) {
    printf("%d人目の身長と体重は\n", i + 1);
    for(int j = 0; j < 2; j++) {
      printf("%d ", human[i][j]);
    }
    printf("\n");
  }

  return 0;
}
