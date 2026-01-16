/* 問題９
• ユーザからのコマンド入力を任意回数受け付けて
その内容をリスト構造に挿入せよ・削除せよ
• ユーザ入力の例
• a kaji,170,80 ->ユーザ新たに挿入
• d kaji ->氏名がkajiの要素削除
• p -> 標準出力に現状を表示
• q -> 終了
• 格納したデータを標準出力に表示すること
• メモリの開放を忘れないこと */
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
  if (m == NULL) {
    return;
  }
  printf("Name: %s, Height: %.2f, Weight: %.2f\n", m->name, m->height,
         m->weight);
  if (m->next != NULL) {
    print_mlist(m->next);
  }
}

Melem *add_melem(Melem *root, const char *name, double height, double weight) {
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
  new_member->next = next;

  if (prev == NULL) {
    return new_member;
  } else {
    prev->next = new_member;
    return root;
  }
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

  // 名前が見つからなかった場合、そのまま返す
  if (next == NULL)
    return root;

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

  char input[128];
  char command;
  char name[64];
  double height, weight;

  printf("a: 追加, d: 削除, p: 表示, q: 終了\n");
  while (1) {
    printf("command: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }
    if (sscanf(input, " %c", &command) != 1) {
      continue;
    }

    switch (command) {
			case 'a':
				// フォーマットが正しいか確認
				if (sscanf(input, " a %[^,],%lf,%lf", name, &height, &weight) == 3) {
					root = add_melem(root, name, height, weight);
				}
				break;
			case 'd':
				// フォーマットが正しいか確認
				if (sscanf(input, " d %s", name) == 1) {
					root = delete_melem(root, name);
				}
				break;
			case 'p':
				print_mlist(root);
				break;
			case 'q':
				free_mlist(root);
				return 0;
			default:
				printf("不明なコマンドです。\n");
    }
  }
}
