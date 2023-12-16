#include "card.h"

Card::Card(int suit = spades, int number = 1) : suit(suit), number(number){
    symbol = (suit == spades) ? "♣" : (suit == hearts) ? "♥" : (suit == diamonds) ? "♦" : "♠";
}
Card::Card(const Card& k) : suit(k.suit), number(k.number), value(k.value), symbol(k.symbol) { }

int Card::showSuit()const{    return suit;    }
int Card::showNumber()const{    return number;    }
void Card::print(){  std::cout<<*this<<std::endl;  }
std::ostream& operator<<(std::ostream& out, Card& k){
    if(k.number!=1 && k.number<11){
        if(k.number<10)
            out<<"╔════╗\n║   "<<k.number<<"║\n║"<<k.symbol<<"   ║\n╚════╝";
        else
            out<<"╔════╗\n║  "<<k.number<<"║\n║"<<k.symbol<<"   ║\n╚════╝";
    }else{
        if(k.number == 1)
            out<<"╔════╗\n║   A║\n║"<<k.symbol<<"   ║\n╚════╝";
        else if(k.number == 11)
            out<<"╔════╗\n║   J║\n║"<<k.symbol<<"   ║\n╚════╝";
        else if(k.number == 12)
            out<<"╔════╗\n║   Q║\n║"<<k.symbol<<"   ║\n╚════╝";
        else
            out<<"╔════╗\n║   K║\n║"<<k.symbol<<"   ║\n╚════╝";
    }
    return out;
}

Deck::Deck() : top(0){
    for(int i = 0; i<52; i++)
        cards[i] = Card(i/13, i%13+1);
}

void Deck::print(){
    for(auto& kart : cards)
        kart.print();
}

void Deck::shuffle(int kere = 100){
    for(int i = 0; i < kere; i++){
        int x = rand()%52;
        int y = rand()%52;
        Card temp;
        temp = cards[x];
        cards[x] = cards[y];
        cards[y] = temp;
    }
}

Card Deck::draw_card(){   return cards[top++];    }