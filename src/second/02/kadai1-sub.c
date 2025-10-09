#include <stdio.h>

#define MAX 1000000000000
#define HUNDRED_MILLION 100000000 // 億
#define TEN_THOUSAND 10000 // 万
#define THOUSAND 1000 // 千
#define HUNDRED 100 // 百

void print_place(long long n, long long place);

long long yomiage(long long n) {
  if (n >= MAX) {
    printf("読めません");
  } else if (n == 0) {
    printf("零");
  } else {
    if (n >= HUNDRED_MILLION) {
      yomiage(n / HUNDRED_MILLION);
      printf("億");
      n = n % HUNDRED_MILLION;
    }
    if (n >= TEN_THOUSAND) {
      yomiage(n / TEN_THOUSAND);
      printf("万");
      n = n % TEN_THOUSAND;
    }
    if (n >= THOUSAND) {
      if (n / THOUSAND > 1) {
        print_place(n, THOUSAND);
      }
      printf("千");
      n = n % THOUSAND;
    }
    if (n >= HUNDRED) {
      if (n / HUNDRED > 1) {
        print_place(n, HUNDRED);
      }
      printf("百");
      n = n % HUNDRED;
    }
    if (n >= 10) {
      if (n / 10 > 1) {
        print_place(n, 10);
      }
      printf("十");
      n = n % 10;
    }
    if (n >= 1) {
      print_place(n, 1);
    }
  }

  return 0;
}

void print_place(long long n, long long place) {
  n /= place;
  printf("%s", (n == 1) ? "一" : (n == 2) ? "二" : (n == 3) ? "三" : (n == 4) ? "四" : (n == 5) ? "五" : (n == 6) ? "六" : (n == 7) ? "七" : (n == 8) ? "八" : (n == 9) ? "九" : "");
}
