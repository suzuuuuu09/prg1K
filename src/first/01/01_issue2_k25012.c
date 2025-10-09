//
//  01_issue2_k25012.c
//  prg1
//
//  Created by k25012kk on 2025/04/10.
//

#include <stdio.h>

int main(int argc, const char *argv[]) {
    // 5/3の余を計算する
    int a = 5;
    int b = 3;
    int remainder = a % b;
    // 余りを表示する
    printf("%d %% %d = %d\n", a, b, remainder);
}

