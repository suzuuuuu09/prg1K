/* 課題
• 問題１０を発展させる
• ファイル読み込み後，ユーザからの入力を任意回数
受け付けて要素を追加/削除できるようにする
• リスト構造の中身を同名ファイルに出力する */
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
  printf("Name: %s, Height: %.0f, Weight: %.0f\n", m->name, m->height,
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

void parse_line(char *line, char *name, double *height, double *weight) {
  char *token = strtok(line, ",");
  strncpy(name, token, 63);
  name[63] = '\0';

  *height = atof(strtok(NULL, ","));
  *weight = atof(strtok(NULL, ","));
}

Melem *read_file(Melem *root, char *filename) {
  // ファイルを読み込む
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("ファイルが開けないよ！");
    return root;
  }
  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    // 行をパースしてメンバーを追加
    char name[64];
    double height, weight;
    parse_line(line, name, &height, &weight);
    root = add_melem(root, name, height, weight);
  }
  fclose(fp);
  return root;
}

/**
 * @brief rootの内容をファイルに書き込む
 *
 * @param root
 * @param filename 書き込むファイル名
 */
void write_file(Melem *root, char *filename) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		perror("ファイルが開けないよ！");
		return;
	}

	Melem *current = root;
	while (current != NULL) {
		fprintf(fp, "%s,%.0f,%.0f\n", current->name, current->height, current->weight);
		current = current->next;
	}
}

int main() {
  Melem *root = NULL;
  root = read_file(root, "meibo.csv");

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
        // rootの内容をファイルに書き込む
				write_file(root, "meibo.csv");
      }
      break;
    case 'd':
      // フォーマットが正しいか確認
      if (sscanf(input, " d %s", name) == 1) {
        root = delete_melem(root, name);
				// rootの内容をファイルに書き込む
				write_file(root, "meibo.csv");
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
