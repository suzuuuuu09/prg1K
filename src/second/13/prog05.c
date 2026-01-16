/* 問題５
• リストを開放するfree_mlistを実装せよ */
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

Melem *add_melem(Melem *root, const char *name, double height, double weight) {
	Melem *p = (Melem *)malloc(sizeof(Melem));

	strncpy(p->name, name, sizeof(p->name) - 1);
	p->name[sizeof(p->name) - 1] = '\0';
	p->height = height;
	p->weight = weight;
	p->next   = root;

	return p;
}


void free_mlist(Melem *m) {
  if (m != NULL) {
    free_mlist(m->next);
    free(m);
  }
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
