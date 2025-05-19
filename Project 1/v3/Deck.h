#include "Card.h"
#include <list>
#include <string>
using namespace std;

class Deck{

    private:
        list<Card> deck;
        int drawCount;      //to help keep count of when to shuffle
        void setDeck();
        void setSpecials();
        Card setCard(string, int);
        Card setCard(string, int, bool);
        Card setCard(string, string, int, bool);
    public:
        Deck();
        void printDeck();
        void printCard(Card);
        void shuffleDeck();
        void pop_back(){deck.pop_back();}
        void push(Card card){deck.push_back(card);}
        Card getTopCard(){return deck.back();}
        int getSize(){return deck.size();}
};