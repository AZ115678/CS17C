#include "Card.h"
#include <list>
#include <string>
using namespace std;

class Deck{

    private:
        list<Card> deck;
        void setDeck();
        void setSpecials();
        void shuffleDeck();
        Card setCard(string, int);
        Card setCard(string, int, bool);
        Card setCard(string, string, int, bool);
    public:
        Deck();
        void printDeck();
        void printCard(Card);
        void pop_back(){deck.pop_back();}
        Card getTopCard(){return deck.back();}
};