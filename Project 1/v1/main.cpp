/*
    Author: Adam Zavala
    Purpose: Uno game for Project 1 of CS 17C Project that utilizes c++ stl.
    Version 1: Sets up cards and deck which utilizes lists from stl. Will turn to its own deck and card class in next version.
*/

#include <iostream>
#include <string>
#include <list>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

struct Card{
    int value;
    string color;
    string name;
    bool isSpecial = false;//default state
};

void printCard(Card);
void printDeck(list<Card>);
string setName(Card);
Card setCard(string, int);
Card setCard(string, int, bool);
Card setCard(string, string, int, bool);
list<Card> setDeck(list<Card>);
list<Card> setSpecials(list<Card>);
list<Card> shuffleDeck(list<Card>);

int main(){
    srand(time(0));
    //set up individual cards to test if they work
    Card red8 = setCard("Red", 8);
    Card wild = setCard("Wild", 0, true);
    //set up a test deck
    list<Card> deck;
    deck = setDeck(deck);
    //print out cards made individually
    printCard(red8);
    printCard(wild);
    //print entire deck
    cout << "Original:\n\n";
    printDeck(deck);
    //shuffle deck function
    deck = shuffleDeck(deck);
    //check if it works
    cout << "\n\nShuffled Deck: \n\n";
    printDeck(deck);

    return 0;
}
//Set Default Color Cards w/ Color and Value
Card setCard(string color, int value){
    Card card;
    card.color = color;
    card.value = value;
    card.name = setName(card);
    return card;
}
//Used to set Card with special traits like wild cards that have no color
Card setCard(string name, int value, bool isSpecial){
    Card card;
    card.name = name;
    card.value = value;
    card.isSpecial = isSpecial;
    return card;
}
//Used to set cards with special traits that also have colors, like reverses, skips, and draw 2s
Card setCard(string name, string color, int value, bool isSpecial){
    Card card;
    card.color = color;
    card.name = color + " " + name;
    card.value = value;
    card.isSpecial = isSpecial;
    return card;
}

list<Card> setDeck(list<Card> deck){
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
    deck = setSpecials(deck);
    return deck;    
}
list<Card> setSpecials(list<Card> deck){
    string color, name;
    for(int i=0;i<4;i++){
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

    return deck;
}
//mash shuffle variation that moves front and back card into rand position inside deck
list<Card> shuffleDeck(list<Card> deck){
    //insert new card into deck, for shuffling later
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
    

    return deck;
}

void printCard(Card card){
    cout << card.name << endl;
}

void printDeck(list<Card> deck){
    for(auto i = deck.begin(); i!=deck.end();++i){
        printCard(*i);
    }
}

string setName(Card card){
    if(card.isSpecial == false){
        return card.color + " " + to_string(card.value);
    }
    else{
        return "default name";
    }
}