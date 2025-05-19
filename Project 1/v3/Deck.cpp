#include "Deck.h"
#include <iostream>
#include <ctime>
using namespace std;

Deck::Deck(){
    setDeck();
    setSpecials();
    shuffleDeck();
}
void Deck::setDeck(){
    //19 each color for normal cards with numbers on it
    //each get 1 set from 0-9, and another from 1-9, 19 total
    int n = 40;
    for(int z=0;z<2;z++){
        for(int i=0;i<n-(z*4);i++){
            int mod = 10;
            if(z==1){
                mod = 9;
            }
            int value = i % mod;
            string color;
            int c = i / mod;
            switch(c){
                case 1:
                    color = "Red";
                    break;
                case 2:
                    color = "Blue";
                    break;
                case 3:
                    color = "Yellow";
                    break;
                case 0:
                    color = "Green";
                    break;
            }
            if(z==1){
                value ++;
            }
            deck.push_back(setCard(color, value));
        }
    }    
}
void Deck::setSpecials(){
    string color, name;
    //loop 4 times for the 4 special types of cards: skip, reverse, wild, & wild +4
    for(int i=0;i<4;i++){
        //8 each of special types, except for wild which only has 4 for base wild and 4 for wild +4
        for(int z=0;z<8;z++){
            if(i==3){
                if(z%2==0){
                    name = "Wild";
                }
                else{
                    name = "Wild Draw +4";
                }
                deck.push_back(setCard(name, z%2, true));
            }
            else{
                switch(i){
                    case 0:
                        name = "Skip";
                        break;
                    case 1:
                        name = "Reverse";
                        break;
                    case 2:
                        name = "Draw +2";
                        break;
                }

                int c = z % 4;
                switch(c){
                    case 1:
                        color = "Red";
                        break;
                    case 2:
                        color = "Blue";
                        break;
                    case 3:
                        color = "Yellow";
                        break;
                    case 0:
                        color = "Green";
                        break;
                }
                deck.push_back(setCard(name, color, i, true));
            }
            
        }
    }
}
//mash shuffle variation that moves front and back card into rand position inside deck
void Deck::shuffleDeck(){
    //insert new card into deck, for shuffling later
    srand(time(0));
    list<Card>::iterator it = deck.begin();
    Card temp;
    int n, pos;
    n = 400;
    for(int i=0;i<n;i++){
        //new card position based on ran num generator
        pos = rand() % 40;
        advance(it, pos);
        //rotates from moving back or front card based on loop iteration being even or odd
        if(i%2==0){
            temp = deck.back();
            deck.emplace(it, temp);
            deck.pop_back();
        }
        else{
            temp = deck.front();
            deck.emplace(it, temp);
            deck.pop_front();
        }
    }
}
//useful function for debug purposes
void Deck::printDeck(){
    for(auto i = deck.begin();i!=deck.end();i++){
        //printCard(*i);
        string n = i->getName();
        cout << n << endl;
    }
}
Card Deck::setCard(string color, int value){
    Card temp(color, value);
    return temp;
}
Card Deck::setCard(string name, int value, bool isSpecial){
    Card temp(name, value, isSpecial);
    return temp;
}
Card Deck::setCard(string name, string color, int value, bool isSpecial){
    Card temp(name, color, value, isSpecial);
    return temp;
}