#include "Card.h"
#include <list>

//using namespace std;
struct Player{
    list<Card> hand;
    int handSize = 0;
};