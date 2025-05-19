/*
    Author: Adam Zavala
    Purpose: Uno game for Project 1 of CS 17C Project that utilizes c++ stl.
    Version 1: Sets up cards and deck which utilizes lists from stl. Will turn to its own deck and card class in next version.
    Version 2: Card and Deck class created.
                Players are created as structures which maps will be utilized to hold all player objects and assign them a unique ID.
                Draw function added.
                Created stack container for discard pile.
                Using Queue container for player turn orders.
    Version 3:
                Game Class created.
*/
//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//#include "Game.h"
#include "Game.h"

//Function Prototypes
int getPlayerCount();

int main(){
    cout << "Welcome to Uno!" << endl;
    int playerCount = getPlayerCount();
    Game game(playerCount);
    game.dealHand();
    game.gameLoop();
    cout << "Thanks for playing!" << endl;
    return 0;
}
//Prompts user for amount of players in game and returns that amount
int getPlayerCount(){
    int n;
    cout << "Please enter total amount of UNO players (Max = 6): ";
    cin >> n;
    if(n<2)n=2;
    if(n>6)n=6;
    //TODO: User validation
    return n;
}