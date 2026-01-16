/* 問題６
• 先頭要素への追加でなく，氏名の辞書順に
追加するようにadd_melemを変更せよ
• 新しいrootのアドレスをreturnすること */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct melem {
	char name[64];
	double height;
	double weight;
	struct melem *next;
} Melem;


void print_mlist(Melem *m) {
	printf("Name: %s, Height: %.2f, Weight: %.2f\n", m->name, m->height, m->weight);
	if (m->next != NULL) {
		print_mlist(m->next);
	}
}

void free_mlist(Melem *m) {
  if (m != NULL) {
    free_mlist(m->next);
    free(m);
  }
}

Melem *add_melem(Melem *root, const char *name, double height, double weight) {
	Melem *next = root;
	Melem *prev = NULL;

	// 新しいメンバーの挿入位置を探す
	while (next != NULL && strcmp(name, next->name) > 0) {
		prev = next;
		next = next->next;
	}

  Melem *new = (Melem *)malloc(sizeof(Melem));

  strncpy(new->name, name, sizeof(new->name) - 1);
  new->name[sizeof(new->name) - 1] = '\0';
  new->height = height;
  new->weight = weight;
  new->next = root;

  return new;
}


int main() {
  Melem *root = NULL;

  root = add_melem(root, "Sanro",  5.8, 150.0);
  root = add_melem(root, "Niro",   6.0, 180.0);
  root = add_melem(root, "Ichiro", 5.5, 130.0);

  print_mlist(root);
	free_mlist(root);

  return 0;
}

