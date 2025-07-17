#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "./lib/text_displayer.c"
#include "./lib/card.c"

// ゲーム関数のプロトタイプ宣言
void initialize_game(GameState* game, char* player_name);
void create_deck(Card* deck);
void deal_cards(GameState* game, Card* deck);
void draw_field_cards(Player* player);
int compare_cards(Card card1, Card card2);
void display_game_state(GameState* game);
void print_cards_with_selection(Card cards[], int count, int selected);
void generate_card_row_for_selection(int suit, int number, int row, char* buffer);
void remove_card_from_field(Player* player, int index);
int select_card(Player* player, bool is_human);
void play_turn(GameState* game);
void handle_war(GameState* game, Card player_card, Card computer_card);
bool check_game_end(GameState* game);
void show_result(GameState* game);
void draw_box(const char* title, const char* content, int width);
void display_game_state_tui(GameState* game);
int select_card_tui(Player* player, bool is_human);
void show_result_tui(GameState* game);
void play_turn_tui(GameState* game);
void handle_war_tui(GameState* game, Card player_card, Card computer_card);
void start_game_tui(char* player_name);

/**
 * @brief ゲームの初期化
 */
void initialize_game(GameState* game, char* player_name) {
    srand(time(NULL));
    
    // プレイヤー初期化
    strcpy(game->player.name, player_name);
    game->player.hand_count = 26;
    game->player.field_count = 0;
    game->player.won_cards = 0;
    
    // コンピュータ初期化
    strcpy(game->computer.name, "Computer");
    game->computer.hand_count = 26;
    game->computer.field_count = 0;
    game->computer.won_cards = 0;
    
    // ゲーム状態初期化
    game->turn = 0;
    game->is_war = false;
    game->war_count = 0;
    
    // デッキ作成とカード配布
    Card deck[52];
    create_deck(deck);
    shuffle_array(deck, 52, sizeof(Card));
    
    deal_cards(game, deck);
}

/**
 * @brief 52枚のデッキを作成
 */
void create_deck(Card* deck) {
    int index = 0;
    for (int suit = 1; suit <= 4; suit++) {
        for (int number = 1; number <= 13; number++) {
            deck[index].suit = suit;
            deck[index].number = number;
            index++;
        }
    }
}

/**
 * @brief カードを配布
 */
void deal_cards(GameState* game, Card* deck) {
    for (int i = 0; i < 26; i++) {
        game->player.hand[i] = deck[i];
        game->computer.hand[i] = deck[i + 26];
    }
}

/**
 * @brief 場にカードを3枚出す
 */
void draw_field_cards(Player* player) {
    if (player->hand_count < 3) {
        // 手札が3枚未満の場合は全て出す
        for (int i = 0; i < player->hand_count; i++) {
            player->field[i] = player->hand[i];
        }
        player->field_count = player->hand_count;
        player->hand_count = 0;
    } else {
        // 手札から3枚を場に出す
        for (int i = 0; i < 3; i++) {
            player->field[i] = player->hand[i];
        }
        player->field_count = 3;
        
        // 手札から出したカードを削除
        for (int i = 0; i < player->hand_count - 3; i++) {
            player->hand[i] = player->hand[i + 3];
        }
        player->hand_count -= 3;
    }
}

/**
 * @brief カードの強さを比較（1: player勝利, -1: computer勝利, 0: 引き分け）
 */
int compare_cards(Card card1, Card card2) {
    int value1 = card1.number;
    int value2 = card2.number;
    
    // Aを14に変換
    if (value1 == 1) value1 = 14;
    if (value2 == 1) value2 = 14;
    
    // 特別ルール: 2はAに勝つ
    if (card1.number == 2 && card2.number == 1) return 1;
    if (card1.number == 1 && card2.number == 2) return -1;
    
    if (value1 > value2) return 1;
    if (value1 < value2) return -1;
    return 0;
}

/**
 * @brief ゲーム状態を表示
 */
void display_game_state(GameState* game) {
    clear_screen();
    printf("\n=== Emperor War - Turn %d ===\n\n", game->turn + 1);
    
    printf("%s: 手札 %d枚, 獲得 %d枚\n", game->player.name, game->player.hand_count, game->player.won_cards);
    printf("%s: 手札 %d枚, 獲得 %d枚\n\n", game->computer.name, game->computer.hand_count, game->computer.won_cards);
    
    if (game->player.field_count > 0) {
        printf("%sの場のカード:\n", game->player.name);
        _print_cards(game->player.field, game->player.field_count);
        printf("\n");
    }
    
    if (game->computer.field_count > 0) {
        printf("%sの場のカード:\n", game->computer.name);
        _print_cards(game->computer.field, game->computer.field_count);
        printf("\n");
    }
}

/**
 * @brief TUI風のボックスを描画する関数
 * @param title タイトル
 * @param content コンテンツ
 * @param width ボックスの幅
 */
void draw_box(const char* title, const char* content, int width) {
    // 上枠
    printf("┌");
    for (int i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("┐\n");
    
    // タイトル行
    if (title) {
        printf("│ %s", title);
        int title_len = strlen(title);
        for (int i = 0; i < width - title_len - 4; i++) {
            printf(" ");
        }
        printf(" │\n");
        
        // 区切り線
        printf("├");
        for (int i = 0; i < width - 2; i++) {
            printf("─");
        }
        printf("┤\n");
    }
    
    // コンテンツ行
    if (content) {
        printf("│ %s", content);
        int content_len = strlen(content);
        for (int i = 0; i < width - content_len - 4; i++) {
            printf(" ");
        }
        printf(" │\n");
    }
    
    // 下枠
    printf("└");
    for (int i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("┘\n");
}

/**
 * @brief ゲーム状態をTUI風に表示
 */
void display_game_state_tui(GameState* game) {
    clear_screen();
    
    // Header with turn information
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                 EMPEROR WAR                                    ║\n");
    printf("║                            Turn %2d / 20 (%.1f%%)                             ║\n", 
           game->turn + 1, ((float)(game->turn + 1) / 20.0) * 100);
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    // Detailed player information
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Player Status                                                                  │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ %-15s: Hand %2d cards | Field %d cards | Won %2d cards | Score %3.1f%% │\n", 
           game->player.name, 
           game->player.hand_count, 
           game->player.field_count,
           game->player.won_cards,
           ((float)game->player.won_cards / 30.0) * 100);
    printf("│ %-15s: Hand %2d cards | Field %d cards | Won %2d cards | Score %3.1f%% │\n", 
           game->computer.name, 
           game->computer.hand_count, 
           game->computer.field_count,
           game->computer.won_cards,
           ((float)game->computer.won_cards / 30.0) * 100);
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    
    // Progress bars for won cards
    printf("│ %s Progress to 30:   [", game->player.name);
    int player_progress = (game->player.won_cards * 20) / 30;
    for (int i = 0; i < 20; i++) {
        if (i < player_progress) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %2d/30       │\n", game->player.won_cards);
    
    printf("│ %s Progress to 30: [", game->computer.name);
    int computer_progress = (game->computer.won_cards * 20) / 30;
    for (int i = 0; i < 20; i++) {
        if (i < computer_progress) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %2d/30       │\n", game->computer.won_cards);
    
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    
    // Turn counter and remaining turns
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Game Progress                                                                  │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Current Turn: %2d                    Remaining Turns: %2d                    │\n", 
           game->turn + 1, 20 - (game->turn + 1));
    printf("│ Turn Progress: [");
    int turn_progress = ((game->turn + 1) * 30) / 20;
    for (int i = 0; i < 30; i++) {
        if (i < turn_progress) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %2d%%        │\n", (int)(((float)(game->turn + 1) / 20.0) * 100));
    
    // War statistics
    printf("│ War Status: %s                    Total Cards in Play: %2d              │\n", 
           game->is_war ? "Active" : "None", 
           game->player.won_cards + game->computer.won_cards);
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    
    // Field cards display
    if (game->player.field_count > 0) {
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ %s's Field Cards (%d cards)                                             │\n", 
               game->player.name, game->player.field_count);
        printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
        printf("│ ");
        
        _print_cards(game->player.field, game->player.field_count);
        
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    }
    
    if (game->computer.field_count > 0) {
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ %s's Field Cards (%d cards)                                            │\n", 
               game->computer.name, game->computer.field_count);
        printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
        printf("│ ");
        
        _print_cards(game->computer.field, game->computer.field_count);
        
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    }
}

/**
 * @brief カードを選択
 */
int select_card(Player* player, bool is_human) {
    if (is_human) {
        int selected = 0;
        char ch;
        
        raw_mode(true);
        
        while (1) {
            clear_screen();
            printf("\n=== %sさん、出すカードを選んでください ===\n\n", player->name);
            
            // カードを選択状態で表示
            print_cards_with_selection(player->field, player->field_count, selected);
            
            printf("\n← → 矢印キーで選択、Enterで決定\n");
            fflush(stdout);
            
            ch = getchar();
            
            if (ch == 27) { // ESCシーケンス
                getchar(); // '['
                ch = getchar(); // 方向キー
                
                switch (ch) {
                    case 'C': // 右矢印
                        selected = (selected + 1) % player->field_count;
                        break;
                    case 'D': // 左矢印
                        selected = (selected - 1 + player->field_count) % player->field_count;
                        break;
                }
            } else if (ch == '\n' || ch == '\r') { // Enter
                break;
            }
        }
        
        raw_mode(false);
        return selected;
    } else {
        // コンピュータはランダムに選択
        return rand() % player->field_count;
    }
}

/**
 * @brief TUI style card selection screen
 */
int select_card_tui(Player* player, bool is_human) {
    if (is_human) {
        int selected = 0;
        char ch;
        
        raw_mode(true);
        
        while (1) {
            clear_screen();
            
            // Header
            printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                            Card Selection                                      ║\n");
            printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
            
            // Player name display
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│ %s, please select a card to play                                           │\n", player->name);
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
            
            // Card selection area
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│ Card Selection                                                                 │\n");
            printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
            printf("│ ");
            
            // Display cards with selection
            print_cards_with_selection(player->field, player->field_count, selected);
            
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            
            // Controls explanation
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│ Controls: ← → Arrow keys to select, Enter to confirm                          │\n");
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            
            fflush(stdout);
            
            ch = getchar();
            
            if (ch == 27) { // ESC sequence
                getchar(); // '['
                ch = getchar(); // Direction key
                
                switch (ch) {
                    case 'C': // Right arrow
                        selected = (selected + 1) % player->field_count;
                        break;
                    case 'D': // Left arrow
                        selected = (selected - 1 + player->field_count) % player->field_count;
                        break;
                }
            } else if (ch == '\n' || ch == '\r') { // Enter
                break;
            }
        }
        
        raw_mode(false);
        return selected;
    } else {
        // コンピュータはランダムに選択
        return rand() % player->field_count;
    }
}

/**
 * @brief ターンの処理
 */
void play_turn(GameState* game) {
    // 場にカードを出す
    draw_field_cards(&game->player);
    draw_field_cards(&game->computer);
    
    display_game_state(game);
    
    // カードを選択（選択する前にカードデータをコピーして保護）
    Card player_selected_card = game->player.field[0]; // 初期化
    Card computer_selected_card = game->computer.field[0]; // 初期化
    
    int player_choice = select_card(&game->player, true);
    int computer_choice = select_card(&game->computer, false);
    
    // 選択されたカードを安全にコピー
    player_selected_card = game->player.field[player_choice];
    computer_selected_card = game->computer.field[computer_choice];
    
    printf("\n%sが出したカード:\n", game->player.name);
    print_card(player_selected_card.suit, player_selected_card.number);
    printf("\n%sが出したカード:\n", game->computer.name);
    print_card(computer_selected_card.suit, computer_selected_card.number);
    
    // 勝敗判定
    int result = compare_cards(player_selected_card, computer_selected_card);
    
    if (result == 0) {
        // 戦争発生
        printf("\n戦争発生！\n");
        handle_war(game, player_selected_card, computer_selected_card);
    } else if (result == 1) {
        // プレイヤー勝利
        printf("\n%sの勝利！\n", game->player.name);
        game->player.won_cards += 2;
        if (game->player.won_cards >= 30) {
            printf("%sが30枚先取で勝利！\n", game->player.name);
            return;
        }
    } else {
        // コンピュータ勝利
        printf("\n%sの勝利！\n", game->computer.name);
        game->computer.won_cards += 2;
        if (game->computer.won_cards >= 30) {
            printf("%sが30枚先取で勝利！\n", game->computer.name);
            return;
        }
    }
    
    // 選択されたカードを場から削除（安全な削除処理）
    remove_card_from_field(&game->player, player_choice);
    remove_card_from_field(&game->computer, computer_choice);
    
    game->turn++;
    
    printf("\nEnterキーで続行...");
    getchar();
}

/**
 * @brief 戦争の処理
 */
void handle_war(GameState* game, Card player_card, Card computer_card) {
    int cards_at_stake = 2; // 最初の2枚
    
    while (true) {
        if (game->player.field_count <= 1 || game->computer.field_count <= 1) {
            printf("戦争を続行できません。引き分けです。\n");
            break;
        }
        
        printf("\n=== 戦争発生！追加のカードを選んでください ===\n");
        printf("現在の賭けカード数: %d枚\n\n", cards_at_stake);
        
        // 現在の場の状況を表示
        printf("%sの場のカード:\n", game->player.name);
        _print_cards(game->player.field, game->player.field_count);
        printf("\n");
        
        printf("%sの場のカード:\n", game->computer.name);
        _print_cards(game->computer.field, game->computer.field_count);
        printf("\n");
        
        int player_choice = select_card(&game->player, true);
        int computer_choice = select_card(&game->computer, false);
        
        // 選択されたカードを安全にコピー
        Card new_player_card = game->player.field[player_choice];
        Card new_computer_card = game->computer.field[computer_choice];
        
        clear_screen();
        printf("\n=== 戦争結果 ===\n");
        printf("%sが出したカード:\n", game->player.name);
        print_card(new_player_card.suit, new_player_card.number);
        printf("\n%sが出したカード:\n", game->computer.name);
        print_card(new_computer_card.suit, new_computer_card.number);
        
        int result = compare_cards(new_player_card, new_computer_card);
        cards_at_stake += 2;
        
        if (result == 1) {
            printf("\n%sが戦争に勝利！%d枚獲得！\n", game->player.name, cards_at_stake);
            game->player.won_cards += cards_at_stake;
            break;
        } else if (result == -1) {
            printf("\n%sが戦争に勝利！%d枚獲得！\n", game->computer.name, cards_at_stake);
            game->computer.won_cards += cards_at_stake;
            break;
        } else {
            printf("\nまた同じ数字！戦争継続！\n");
            printf("Enterキーで戦争を続行...");
            getchar();
        }
        
        // 使用したカードを安全に削除
        remove_card_from_field(&game->player, player_choice);
        remove_card_from_field(&game->computer, computer_choice);
    }
}

/**
 * @brief ゲーム終了判定
 */
bool check_game_end(GameState* game) {
    // 手札がなくなった場合
    if (game->player.hand_count == 0 && game->player.field_count == 0) {
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               Game Over                                        ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ %s has no cards left!                                                      │\n", game->player.name);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        return true;
    }
    if (game->computer.hand_count == 0 && game->computer.field_count == 0) {
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               Game Over                                        ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ %s has no cards left!                                                     │\n", game->computer.name);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        return true;
    }
    
    // 30枚先取
    if (game->player.won_cards >= 30) {
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               Game Over                                        ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ 🏆 %s wins with 30 cards! 🏆                                              │\n", game->player.name);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        return true;
    }
    if (game->computer.won_cards >= 30) {
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               Game Over                                        ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ 🏆 %s wins with 30 cards! 🏆                                           │\n", game->computer.name);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        return true;
    }
    
    // 20ターン経過
    if (game->turn >= 20) {
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               Game Over                                        ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ 20 turns have passed! Final score will determine the winner.                  │\n");
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        return true;
    }
    
    return false;
}

/**
 * @brief 結果表示
 */
void show_result(GameState* game) {
    printf("\n=== ゲーム終了 ===\n");
    printf("%s: %d枚獲得\n", game->player.name, game->player.won_cards);
    printf("%s: %d枚獲得\n", game->computer.name, game->computer.won_cards);
    
    if (game->player.won_cards > game->computer.won_cards) {
        printf("\n%sの勝利！\n", game->player.name);
    } else if (game->computer.won_cards > game->player.won_cards) {
        printf("\n%sの勝利！\n", game->computer.name);
    } else {
        printf("\n引き分け！\n");
    }
}

/**
 * @brief TUI風の結果表示
 */
void show_result_tui(GameState* game) {
    clear_screen();
    
    // Header
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Game Over                                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    // Final results
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Final Results                                                                  │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ %-15s: %2d cards won                                                    │\n", 
           game->player.name, game->player.won_cards);
    printf("│ %-15s: %2d cards won                                                    │\n", 
           game->computer.name, game->computer.won_cards);
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    
    // Winner announcement
    if (game->player.won_cards > game->computer.won_cards) {
        printf("│                           🎉 %s Victory! 🎉                                 │\n", game->player.name);
    } else if (game->computer.won_cards > game->player.won_cards) {
        printf("│                           🎉 %s Victory! 🎉                              │\n", game->computer.name);
    } else {
        printf("│                                Draw Game!                                     │\n");
    }
    
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    
    // Game statistics
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Game Statistics                                                                │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ Total Turns: %2d                                                              │\n", game->turn);
    printf("│ War Occurred: %s                                                             │\n", 
           game->is_war ? "Yes" : "No");
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
}

/**
 * @brief 選択されたカードをハイライト表示する関数
 * @param cards カードの配列
 * @param count カードの数
 * @param selected 選択されたカードのインデックス
 */
void print_cards_with_selection(Card cards[], int count, int selected) {
    char buffer[150];
    
    // 各行を順番に出力
    for (int row = 0; row < CARD_HEIGHT; row++) {
        for (int i = 0; i < count; i++) {
            if (i == selected) {
                // 選択されたカードのみ特別な表示
                generate_card_row_for_selection(cards[i].suit, cards[i].number, row, buffer);
                printf("%s", buffer);
            } else {
                // 選択されていないカードは元のcard.cの関数を直接使用
                // カードデータを一切変更せずに表示
                Card original_card = cards[i];
                generate_card_row(original_card.suit, original_card.number, row, buffer);
                printf("%s", buffer);
            }
            
            if (i < count - 1) {
                printf("%*s", CARD_SPACING, ""); // カード間のスペース
            }
        }
        printf("\n");
    }
    
    // 選択インジケーターを表示
    for (int i = 0; i < count; i++) {
        if (i == selected) {
            printf("   ↑   ");
        } else {
            printf("       ");
        }
        
        if (i < count - 1) {
            printf("%*s", CARD_SPACING, "");
        }
    }
    printf("\n");
    
    fflush(stdout);
}

/**
 * @brief 選択用のカード行を生成する関数（反転表示対応）
 * @param suit スート
 * @param number 数字
 * @param row 行番号 (0-4)
 * @param buffer 出力バッファ
 */
void generate_card_row_for_selection(int suit, int number, int row, char* buffer) {
    // {0, 0}の場合は空白のカードを表示
    if (suit == 0 && number == 0) {
        switch (row) {
            case 0:
                strcpy(buffer, "\033[47m\033[30m┌─────┐\033[0m");
                break;
            case 1:
            case 2:
            case 3:
                strcpy(buffer, "\033[47m\033[30m│     │\033[0m");
                break;
            case 4:
                strcpy(buffer, "\033[47m\033[30m└─────┘\033[0m");
                break;
        }
        return;
    }
    
    const char* suit_str = SUIT_SYMBOLS[suit - 1];
    const char* number_str = NUMBER_SYMBOLS[number - 1];
    bool is_red = is_red_suit(suit);
    
    switch (row) {
        case 0:
            strcpy(buffer, "\033[47m\033[30m┌─────┐\033[0m");
            break;
        case 1: // 左上の数字
            if (is_red) {
                snprintf(buffer, 150, "\033[47m\033[31m│%-4s \033[30m│\033[0m", number_str);
            } else {
                snprintf(buffer, 150, "\033[47m\033[30m│%-4s │\033[0m", number_str);
            }
            break;
        case 2: // スート
            if (is_red) {
                snprintf(buffer, 150, "\033[47m\033[31m│  %s  \033[30m│\033[0m", suit_str);
            } else {
                snprintf(buffer, 150, "\033[47m\033[30m│  %s  │\033[0m", suit_str);
            }
            break;
        case 3: // 右下の数字
            if (is_red) {
                snprintf(buffer, 150, "\033[47m\033[31m│ %4s\033[30m│\033[0m", number_str);
            } else {
                snprintf(buffer, 150, "\033[47m\033[30m│ %4s│\033[0m", number_str);
            }
            break;
        case 4: // 下枠
            strcpy(buffer, "\033[47m\033[30m└─────┘\033[0m");
            break;
    }
}

/**
 * @brief ゲームのメイン処理
 */
void start_game(char* player_name) {
    GameState game;
    initialize_game(&game, player_name);
    
    printf("\n=== ゲーム開始 ===\n");
    printf("ルール: 各ターンで3枚のカードを場に出し、1枚を選んで勝負します。\n");
    printf("カードの強さ: A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2\n");
    printf("特別ルール: 2はAに勝ちます！\n");
    printf("勝利条件: 30枚先取、または20ターン後に多く獲得した方の勝利\n\n");
    
    printf("Enterキーでゲーム開始...");
    getchar();
    
    while (!check_game_end(&game)) {
        play_turn(&game);
    }
    
    show_result(&game);
}

/**
 * @brief TUI風のターンの処理
 */
void play_turn_tui(GameState* game) {
    // 場にカードを出す
    draw_field_cards(&game->player);
    draw_field_cards(&game->computer);
    
    display_game_state_tui(game);
    
    // カードを選択（選択する前にカードデータをコピーして保護）
    Card player_selected_card = game->player.field[0]; // 初期化
    Card computer_selected_card = game->computer.field[0]; // 初期化
    
    int player_choice = select_card_tui(&game->player, true);
    int computer_choice = select_card_tui(&game->computer, false);
    
    // 選択されたカードを安全にコピー
    player_selected_card = game->player.field[player_choice];
    computer_selected_card = game->computer.field[computer_choice];
    
    // 結果表示
    clear_screen();
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Battle Result                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Cards Played                                                                   │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ %s:\n", game->player.name);
    print_card(player_selected_card.suit, player_selected_card.number);
    printf("│ %s:\n", game->computer.name);
    print_card(computer_selected_card.suit, computer_selected_card.number);
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    
    // 勝敗判定
    int result = compare_cards(player_selected_card, computer_selected_card);
    
    if (result == 0) {
        // 戦争発生
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│                               ⚔️ WAR DECLARED! ⚔️                             │\n");
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        handle_war_tui(game, player_selected_card, computer_selected_card);
    } else if (result == 1) {
        // プレイヤー勝利
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│                           🎉 %s Victory! 🎉                                 │\n", game->player.name);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        game->player.won_cards += 2;
        if (game->player.won_cards >= 30) {
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│                          🏆 %s wins with 30 cards! 🏆                       │\n", game->player.name);
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            return;
        }
    } else {
        // コンピュータ勝利
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│                           🎉 %s Victory! 🎉                              │\n", game->computer.name);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
        game->computer.won_cards += 2;
        if (game->computer.won_cards >= 30) {
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│                          🏆 %s wins with 30 cards! 🏆                    │\n", game->computer.name);
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            return;
        }
    }
    
    // 選択されたカードを場から削除（安全な削除処理）
    remove_card_from_field(&game->player, player_choice);
    remove_card_from_field(&game->computer, computer_choice);
    
    game->turn++;
    
    printf("\n┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Press Enter to continue to next turn...                                       │\n");
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
    getchar();
}

/**
 * @brief TUI風の戦争の処理
 */
void handle_war_tui(GameState* game, Card player_card, Card computer_card) {
    int cards_at_stake = 2; // Initial 2 cards
    
    while (true) {
        if (game->player.field_count <= 1 || game->computer.field_count <= 1) {
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│                      Cannot continue war. Draw game.                          │\n");
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            break;
        }
        
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               ⚔️ WAR! ⚔️                                      ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ Cards at stake: %2d                                                           │\n", cards_at_stake);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
        
        // Display current field situation
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ %s's Field Cards                                                        │\n", game->player.name);
        printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
        printf("│ ");
        _print_cards(game->player.field, game->player.field_count);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
        
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ %s's Field Cards                                                           │\n", game->computer.name);
        printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
        printf("│ ");
        _print_cards(game->computer.field, game->computer.field_count);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
        
        int player_choice = select_card_tui(&game->player, true);
        int computer_choice = select_card_tui(&game->computer, false);
        
        // Safely copy selected cards
        Card new_player_card = game->player.field[player_choice];
        Card new_computer_card = game->computer.field[computer_choice];
        
        clear_screen();
        printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                               War Result                                       ║\n");
        printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
        
        printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│ War Cards Played                                                               │\n");
        printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
        printf("│ %s:\n", game->player.name);
        print_card(new_player_card.suit, new_player_card.number);
        printf("│ %s:\n", game->computer.name);
        print_card(new_computer_card.suit, new_computer_card.number);
        printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
        
        int result = compare_cards(new_player_card, new_computer_card);
        cards_at_stake += 2;
        
        if (result == 1) {
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│                    🎉 %s wins the war! %d cards won! 🎉                    │\n", game->player.name, cards_at_stake);
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            game->player.won_cards += cards_at_stake;
            break;
        } else if (result == -1) {
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│                    🎉 %s wins the war! %d cards won! 🎉                 │\n", game->computer.name, cards_at_stake);
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            game->computer.won_cards += cards_at_stake;
            break;
        } else {
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│                        Same number again! War continues!                      │\n");
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
            printf("│ Press Enter to continue the war...                                            │\n");
            printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
            getchar();
        }
        
        // Safely remove used cards
        remove_card_from_field(&game->player, player_choice);
        remove_card_from_field(&game->computer, computer_choice);
    }
}

/**
 * @brief TUI style game start screen
 */
void start_game_tui(char* player_name) {
    GameState game;
    initialize_game(&game, player_name);
    
    clear_screen();
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               Game Start                                       ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Game Rules                                                                     │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ • Each turn, draw 3 cards to the field and select 1 to play                   │\n");
    printf("│ • Card strength: A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2          │\n");
    printf("│ • Special rule: 2 beats A!                                                     │\n");
    printf("│ • Win condition: First to 30 cards, or most cards after 20 turns             │\n");
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n\n");
    
    printf("┌─────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Press Enter to start the game...                                              │\n");
    printf("└─────────────────────────────────────────────────────────────────────────────┘\n");
    getchar();
    
    while (!check_game_end(&game)) {
        play_turn_tui(&game);
    }
    
    show_result_tui(&game);
}

/**
 * @brief 場からカードを安全に削除する関数
 * @param player プレイヤー
 * @param index 削除するカードのインデックス
 */
void remove_card_from_field(Player* player, int index) {
    if (index < 0 || index >= player->field_count) {
        return; // 無効なインデックスの場合は何もしない
    }
    
    // 削除するカードより後ろのカードを前に移動
    for (int i = index; i < player->field_count - 1; i++) {
        player->field[i] = player->field[i + 1];
    }
    
    // フィールドのカード数を減らす
    player->field_count--;
    
    // 削除後の最後の位置をクリア（安全のため）
    if (player->field_count >= 0) {
        player->field[player->field_count].suit = 0;
        player->field[player->field_count].number = 0;
    }
}

/**
 * @brief メイン関数
 */
int main() {
    clear_screen();
    print_interval_line(LOGO, 0.1);
    sleep_seconds(0.3);
    
    char name[11];
    
    print_interval("Please enter your name: ", 0.05);
    input_limit(name, 10);
    sprint_interval(0.05, "Hello %s!\n", name);
    sleep_seconds(0.5);
    print_interval("Let's start the Emperor War!\n", 0.05);
    sleep_seconds(0.5);
    
    start_game_tui(name);
    
    return 0;
}