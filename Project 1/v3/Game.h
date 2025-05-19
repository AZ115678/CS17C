#include "Deck.h"
#include "Player.h"
#include <map>
#include <stack>
using namespace std;

class Game{

    private:
        Deck deck;
        map<int, Player> players;
        int playerCount;
        void drawCards(Player&, int);
        void printHand(Player);
        bool playerTurn(Player&, stack<Card>&);
        bool npcTurn(Player&, stack<Card>&, int);
        void setWildColor(Card &, string);
        void setWildColor(Card &);
        void playCard(Player &, Card);
        int getNextPlayer(int, int, bool);
        bool checkMatch(Card, Card);
        bool checkWild(Card);
        bool checkSkip(Card);
        bool checkReverse(Card);
        int checkDraw(Card);
        bool checkWin(Player, int);
        list<Card>::iterator findPlayableCard(Player&, Card);
        void playerConfirmation();
        void reshuffle(stack<Card>&);
    public:
        Game(int);
        void dealHand();
        void gameLoop();
        
};