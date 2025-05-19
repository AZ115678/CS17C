#include <string>
using namespace std;

#ifndef CARD_H
#define CARD_H

class Card{

    private:
        int value;
        string color, name;
        bool isSpecial = false;

    public:
        Card();
        Card(string, int);
        Card(string, int, bool);
        Card(string, string, int, bool);
        string getName(){return name;}
        void setColor(string);
        string getColor(){return color;}
        int getValue(){return value;}
        bool special(){return isSpecial;}
};
#endif // CARD_H