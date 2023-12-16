#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "card.h"

class Blackjack : public Deck {
private:
    bool isdouble = false;
    bool avaibleForSplit = false;
      
public:
    Card dealer[11];
    Card player[11];

    int player_sum;
    int dealer_sum;
    int player_count;
    int dealer_count;
    int isblackjack;
    int won;
    int played; 
    std::string result;
    
    
    Blackjack(bool);
    void start_game();
    void game();
    void show_dealer();
    void show_hand(Card[], int);
    void deal_cards();
    void request_card();
    virtual void open_dealer_hand();
    bool check(int);
    int isbj(Card[], int, int&);
};

class SplitCard : public Blackjack {
private:
    Card* split_card;
    int split_count;
    int split_sum;
    int s_isblackjack;
    std::string player_info, split_info, second_result;

public:
    SplitCard(Blackjack&);
    void request_card(int);
    void split_double();
    void open_dealer_hand()override;
    bool check(int, int);
    ~SplitCard();
};
#include "blackjack.cpp"
#endif