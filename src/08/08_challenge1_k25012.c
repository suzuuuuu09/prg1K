#include <stdio.h>

int main() {
  int input;

  printf("input? ");
  scanf("%d", &input);

  for(int i=2;i*i<=input;i++)
  {
    while(input%i==0)
    {
      input /= i;
      printf("%d", i);
      if(input != 1)
        printf(", ");
      else
        break;
    }
  }
  if(input != 1)
    printf("%d",input);

  printf("\n");
  return 0;
}
