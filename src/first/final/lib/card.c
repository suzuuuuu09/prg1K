#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "./types.c"

#define CARD_HEIGHT 5 /* カードの高さ */
#define CARD_SPACING 3 /* 複数のカードを出すときのスペースサイズ */

#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"

// これで配列の長さ計算しないとなぜかエラーなる
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/*
 * @brief 配列でカードを横並びで出力する関数
 * @param cards Card構造体の配列
*/
#define print_cards(cards) _print_cards(cards, ARRAY_SIZE(cards));

static const char* SUIT_SYMBOLS[] = {"♠", "♣", "❤︎", "♦"};
static const char* NUMBER_SYMBOLS[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

/**
 * @brief スートがダイヤかハート(赤色のスート)かどうかを判定する関数
 * @param suit スート
 * @return 赤色の場合true、黒色の場合false
 */
bool is_red_suit(int suit) {
    bool is_red = (suit == 3 || suit == 4); // ハートまたはダイヤ
    return is_red;
}

/**
 * @brief カードの各行を生成する関数
 * @param suit スート
 * @param number 数字
 * @param row 行番号 (0-4)
 * @param buffer 出力バッファ
 */
void generate_card_row(int suit, int number, int row, char* buffer) {
    // {0, 0}の場合は空白のカードを表示
    if (suit == 0 && number == 0) {
        switch (row) {
            case 0:
                strcpy(buffer, "┌─────┐");
                break;
            case 1:
            case 2:
            case 3:
                strcpy(buffer, "│     │");
                break;
            case 4:
                strcpy(buffer, "└─────┘");
                break;
        }
        return;
    }
    
    const char* suit_str = SUIT_SYMBOLS[suit - 1];
    const char* number_str = NUMBER_SYMBOLS[number - 1];
    bool is_red = is_red_suit(suit);
    
    switch (row) {
        case 0:
            strcpy(buffer, "┌─────┐");
            break;
        case 1: // 左上の数字
            if (is_red) {
                snprintf(buffer, 100, "│%s%-4s%s │", COLOR_RED, number_str, COLOR_RESET);
            } else {
                snprintf(buffer, 100, "│%-4s │", number_str);
            }
            break;
        case 2: // スート
            if (is_red) {
                snprintf(buffer, 100, "│  %s%s%s  │", COLOR_RED, suit_str, COLOR_RESET);
            } else {
                snprintf(buffer, 100, "│  %s  │", suit_str);
            }
            break;
        case 3: // 右下の数字
            if (is_red) {
                // 右詰め
                snprintf(buffer, 100, "│ %s%4s%s│", COLOR_RED, number_str, COLOR_RESET);
            } else {
                snprintf(buffer, 100, "│ %4s│", number_str);
            }
            break;
        case 4: // 下枠
            strcpy(buffer, "└─────┘");
            break;
    }
}

/**
 * @brief トランプのカードを出力する関数
 * @param suit スート (1:♠, 2:♣, 3:❤︎, 4:♦)
 * @param number 数字 (1:A, 2-10:数字, 11:J, 12:Q, 13:K)
 */
void print_card(int suit, int number) {
    char buffer[50];
    for (int row = 0; row < CARD_HEIGHT; row++) {
        generate_card_row(suit, number, row, buffer);
        printf("%s\n", buffer);
    }
    fflush(stdout); // 出力を即座に反映
}

/**
 * @brief 配列でカードを横並びで出力する関数
 * @param cards Card構造体の配列
 * @param count カードの枚数
 */
void _print_cards(Card cards[], int count) {
    char buffer[50];
    
    // 各行を順番に出力
    for (int row = 0; row < CARD_HEIGHT; row++) {
        for (int i = 0; i < count; i++) {
            generate_card_row(cards[i].suit, cards[i].number, row, buffer);
            printf("%s", buffer);
            
            if (i < count - 1) {
                printf("%*s", CARD_SPACING, ""); // カード間のスペース
            }
        }
        printf("\n");
    }
    fflush(stdout); // 出力を即座に反映
}
