#pragma once

// カードの構造体
typedef struct {
    int suit;   // スート（1: スペード, 2: クラブ, 3: ハート, 4: ダイヤ）
    int number;   // 1-13
} Card;

// プレイヤーの構造体
typedef struct {
    Card hand[26];      // 手札
    int hand_count;     // 手札の枚数
    Card field[3];      // 場に出しているカード
    int field_count;    // 場に出しているカードの枚数
    int won_cards;      // 獲得したカード数
    char name[11];      // プレイヤー名
} Player;

// ゲーム状態の構造体
typedef struct {
    Player player;      // プレイヤー
    Player computer;    // コンピュータ
    int turn;          // ターン数
    bool is_war;       // 戦争状態かどうか
    Card war_cards[10]; // 戦争で出されたカード
    int war_count;     // 戦争カード数
} GameState;
