/* 問題３
• 標準出力に表示する関数
print_mlistを実装せよ */
#include <stdio.h>

typedef struct melem {
	char name[64];
	double height;
	double weight;
	struct melem *next;
} melem;


void print_mlist(melem *m) {
	printf("Name: %s, Height: %.2f, Weight: %.2f\n", m->name, m->height, m->weight);
	if (m->next != NULL) {
		print_mlist(m->next);
	}
}

int main() {
	melem *root = NULL;

	melem m1 = { "Ichiro", 5.5, 130.0, NULL };
	melem m2 = { "Niro",   6.0, 180.0, NULL };
	melem m3 = { "Sanro",  5.8, 150.0, NULL };
	
	root = &m1;
	m1.next = &m2;
	m2.next = &m3;
	
	print_mlist(root);
	
	return 0;
}


