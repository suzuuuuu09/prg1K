/* 問題１
• 名簿管理のためのリスト構造を表す構造体
struct melemを実装せよ
• データ
• name
• height
• weight
• ポインタ
• next */
#include <stdio.h>

typedef struct melem {
	char name[64];
	double height;
	double weight;
	struct Melem *next;
} Melem;

