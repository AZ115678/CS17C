/*
    Author: Adam Zavala
    Purpose: Uno game for Project 1 of CS 17C Project that utilizes c++ stl.
    Version 1: Sets up cards and deck which utilizes lists from stl. Will turn to its own deck and card class in next version.
    Version 2: Card and Deck class created.
                Players are created as structures which maps will be utilized to hold all player objects and assign them a unique ID.
                Draw function added.
                Created stack container for discard pile.
                Using Queue container for player turn orders.
*/
//System Libraries
#include <iostream>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

//User Libraries
#include "Deck.h"
struct Player{
    list<Card> hand;
    int handSize = 0;
};

//Function Prototyps
void dealHand(map<int, Player>&, Deck&, int);
void drawCards(Player&, Deck&, int);
void printHand(Player);
void gameLoop(map<int, Player>&, Deck&, int);

int main(){
    cout << "Welcome to Uno!" << endl;
    Deck deck;
    //initialize players;
    Player p;
    Player joe;
    Player cass;
    Player lana;
    //map them to unique ids
    map<int, Player> players = {{0, p}, {1, joe}, {2, cass}, {3, lana}};
    dealHand(players, deck, 4);

    gameLoop(players, deck, 4);
    
    return 0;
}
//function that handles drawing cards. can change based on game.
void drawCards(Player &p, Deck &deck, int drawCount){
    int n = drawCount;
    for(int i=0;i<n;i++){
        p.hand.push_back(deck.getTopCard());
        deck.pop_back();
        p.handSize ++;
    }
}
//Prints player hand when called
void printHand(Player p){
    cout << "\n\nPlayer Hand (" << p.handSize << " cards):\n\n";
    for(auto i=p.hand.begin();i!=p.hand.end();i++){
        //calls getName function from card class which returns the card name as string
        cout << i->getName() << endl;
    }
}
//Only to be called at very start of new Uno game
//Each player recieves 7 cards per Uno rules
void dealHand(map<int, Player> &players, Deck &deck, int playerCount){
    int n = playerCount;
    for(int i=0;i<n;i++){
        drawCards(players[i], deck, 7);
    }
}
//Handles player turn orders and card actions that have been played
void gameLoop(map<int, Player> &players, Deck &deck, int playerCount){
    //Discard pile utilizes stack container because we really only need to see the "top" card of this stack
    stack<Card> discardPile;
    //Queue's first in, first out behaviour makes it easy to handle turn orders
    //Will start off in clockwise rotation, and then reverse order if a reverse card is played
    queue<int> turnOrder;
    int n = playerCount;
    int count = 0;      //used only for simulating turns up to a certain count
    bool win = false;
    bool reverse = false;
    bool skip;
    //before the game loop officially starts, we take the top card of the deck and put it into discard to start the game
    discardPile.push(deck.getTopCard());
    deck.pop_back();

    cout << "Simulating game loop" << endl;
    
    //first player will eventually be decided at random
    int next = 0;
    turnOrder.push(0);
    int mod = 1;

    //start the loop, and only end it when a winner has been declared
    while(win==false){
        //start by resetting states from previous loops
        skip = false;
        mod = 1;

        //this section will be for player actions, for now its only simulated
        cout << "Player " << turnOrder.front() << "'s turn" << endl;
        turnOrder.pop();

        count ++;
        //this loop section implements special card actions like reverses/skips/wilds if applicable
        //will turn into its own functions
                
        if(count%8==0 && count>0){
            cout << "\n\nReverse!\n\n";
            reverse = !reverse;
        }
        if(count == 13 || count == 17){
            skip = true;
            cout << "OOf, player got skipped!" << endl;
        }
        //if a skip is played, mod = 2, meaning
        if(skip == true){
            mod = 2;
        }
        if(reverse == false){
            next +=mod;
            next %= n;
        }
        else{
            if(next == 0){
                next = n-mod;
            }
            else{
                next -=mod;
                next %= n;
            }
        }
        turnOrder.push(next);
        if(count==24){
            win = true;
        }
    }

}