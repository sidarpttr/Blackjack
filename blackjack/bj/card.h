#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <time.h>
#include <windows.h>
#include <string>

#define hearts (0)
#define diamonds (1)
#define clubs (2)
#define spades (3)

#define ace (1)
#define jack (11)
#define queen (12)
#define king (13)


class Card{
public:
    int suit;
    int number;

    int value;
    std::string symbol;
    Card(int, int);
    Card(const Card& k);

    int showSuit()const;
    int showNumber()const;
    void print();
    
    friend std::ostream& operator<<(std::ostream&, Card&);
    
};


class Deck{
protected:
    
public:
    int top;
    Card cards[52];
    Deck();
    void print();
    void shuffle(int);
    Card draw_card();

};

#include "card.cpp"
#endif