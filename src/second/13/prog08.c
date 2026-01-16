/* 問題８
• 指定された名前の要素を削除する
delete_melemを実装せよ
• 削除対象要素のfreeを忘れずに */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Melem {
  char name[64];
  double height;
  double weight;
  struct Melem *next;
} Melem;

void print_mlist(Melem *m) {
  printf("Name: %s, Height: %.2f, Weight: %.2f\n", m->name, m->height,
         m->weight);
  if (m->next != NULL) {
    print_mlist(m->next);
  }
}

Melem *add_melem(Melem *root, const char *name, double height,
                   double weight) {
  Melem *next = root;
  Melem *prev = NULL;

  while (next != NULL && strcmp(name, next->name) > 0) {
    prev = next;
    next = next->next;
  }

  if (next != NULL && strcmp(name, next->name) == 0) {
    // 名前が同じメンバーが存在する場合、情報を更新して終了
    next->height = height;
    next->weight = weight;
    return root;
  }

  Melem *new_member = (Melem *)malloc(sizeof(Melem));

  strncpy(new_member->name, name, sizeof(new_member->name) - 1);
  new_member->name[sizeof(new_member->name) - 1] = '\0';
  new_member->height = height;
  new_member->weight = weight;
  new_member->next = root;

  return new_member;
}

void free_mlist(Melem *m) {
  if (m != NULL) {
    free_mlist(m->next);
    free(m);
  }
}

Melem *delete_melem(Melem *root, const char *name) {
	Melem *next = root;
	Melem *prev = NULL;

	while (next != NULL && strcmp(name, next->name) != 0) {
		prev = next;
		next = next->next;
	}

	if (next == NULL) {
		// 名前が見つからなかった場合、そのまま返す
		return root;
	}

	if (prev == NULL) {
		// 削除するメンバーが先頭の場合
		Melem *new_root = next->next;
		free(next);
		return new_root;
	} else {
		// 削除するメンバーが途中または末尾の場合
		prev->next = next->next;
		free(next);
		return root;
	}
}

int main() {
  Melem *root = NULL;

	/* clang-format off */
  root = add_melem(root, "Sanro",  5.8, 150.0);
  root = add_melem(root, "Niro",   6.0, 180.0);
  root = add_melem(root, "Ichiro", 5.5, 130.0);
  root = add_melem(root, "Niro",   8.0, 160.0); // 同じ名前で追加する
	root = delete_melem(root, "Niro"); // メンバーを削除する
	/* clang-format on */

  print_mlist(root);
  free_mlist(root);

  return 0;
}

