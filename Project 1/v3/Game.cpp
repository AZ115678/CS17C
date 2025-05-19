#include "Game.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <queue>
#include <stack>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

Game::Game(int n){
    playerCount = n;
    for(int i=0;i<playerCount-1;i++){
        players[i] = Player();
    }
}
//Only to be called at very start of new Uno game
//Each player recieves 7 cards per Uno rules
void Game::dealHand(){
    int n = playerCount;
    for(int i=0;i<n;i++){
        drawCards(players[i], 7);
    }
}
//function that handles drawing cards. can change based on game.
void Game::drawCards(Player &p, int drawCount){
    int n = drawCount;
    for(int i=0;i<n;i++){
        p.hand.push_back(deck.getTopCard());
        deck.pop_back();
        p.handSize ++;
    }
    if(deck.getSize() < 20){
        cout << "You guys decide it's time to reshuffle the deck!" << endl;
    }
}
//Prints player hand when called
void Game::printHand(Player p){
    int count = 1;
    cout << "\nPlayer Hand (" << p.handSize << " cards):\n\n";
    for(auto i=p.hand.begin();i!=p.hand.end();i++){
        //calls getName function from card class which returns the card name as string
        cout << count << ": " << i->getName() << endl;
        count ++;
    }
    cout << endl;
}
//Handles player turn orders and card actions that have been played
void Game::gameLoop(){
    //Discard pile utilizes stack container because we really only need to see the "top" card of this stack
    stack<Card> discardPile;
    //Queue's first in, first out behaviour makes it easy to handle turn orders
    //Will start off in clockwise rotation, and then reverse order if a reverse card is played
    queue<int> turnOrder;
    int n = playerCount;
    int winner;
    int count = 0;      //used only for simulating turns up to a certain count
    //game flags
    bool win = false;
    bool quit = false;
    bool reverse = false;
    bool skip;
    bool played;        //keeps track if a player was able to play a card or not
    //before the game loop officially starts, we take the top card of the deck and put it into discard to start the game
    discardPile.push(deck.getTopCard());
    deck.pop_back();
    cout << "First card is: " << discardPile.top().getName() << endl;
    playerConfirmation();
    if(checkWild(discardPile.top())==true){
        setWildColor(discardPile.top());
    }
    
    //first player will eventually be decided at random
    //player 0 is us
    int next = 0;
    turnOrder.push(0);
    int mod = 1;

    //start the loop, and only end it when a winner has been declared
    while(win==false&&quit==false){
        //start by resetting states from previous loops
        skip = false;
        mod = 1;
        //check if deck needs to be reshuffled
        if(deck.getSize()<25){
            cout << "The deck seems to be getting low, time for a reshuffle!" << endl;
            reshuffle(discardPile);
            playerConfirmation();
        }
        //determinds if current turn belongs to you or npc player
        if(turnOrder.front()==0){
            played = playerTurn(players[next], discardPile);
        }
        else{
            played = npcTurn(players[next], discardPile, turnOrder.front());
            playerConfirmation();
        }
        win = checkWin(players[next], turnOrder.front());
        if(win==true){
            break;
        }
        turnOrder.pop();
        //check flags if card was played
        if(played == true){
            skip = checkSkip(discardPile.top());
            if(checkReverse(discardPile.top())==true){
                //if reverse was played, go the other way
                cout << "Reverse played! Turn order is reversed!\n";
                reverse = !reverse;
            }
            if(checkDraw(discardPile.top())>0){
                int temp = (next + 1)%n;
                temp = getNextPlayer(next, mod, reverse);
                drawCards(players[temp], checkDraw(discardPile.top()));
            }
            playerConfirmation();
        }
        //this loop section implements special card actions like reverses/skips/wilds if applicable
        //if a skip is played, mod = 2, meaning, that we jump to the second guy who is next
        if(skip == true){
            mod = 2;
        }
        next = getNextPlayer(next, mod, reverse);
        turnOrder.push(next);
    }
    if(next == 0){
        cout << "You win!" << endl;
    } 
    else{
        cout << "Player " << next << " wins!" << endl;
    }

}
bool Game::checkMatch(Card playerCard, Card card){
    //return true if player's card is wild, which can be played on anything
    if(playerCard.getName()=="Wild"||playerCard.getName()=="Wild Draw +4"){
        return true;
    }
    if(card.special()==false){
        if(playerCard.special()==true){
            return playerCard.getColor()==card.getColor();
        }
        else{
            if(playerCard.getColor()==card.getColor()||playerCard.getValue()==card.getValue()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        if(playerCard.getColor()==card.getColor()||playerCard.getValue()==card.getValue()){
            return true;
        }
        return false;
    }
}
//handles player turn, returns true if they were able to play a valid card
//returns false if they were only able to draw
bool Game::playerTurn(Player &p, stack<Card> &discardPile){
    int input, cInd;
    list<Card> playable;
    Card card = discardPile.top();
    cout << "\nYour turn: " << endl;
    cout << "Card to Match: " << endl << card.getName() << endl;
    printHand(p);
    do{
        //look for playable cards in hand and if none are available, automatically draw a card
        auto it = findPlayableCard(p, card);
        if(it==p.hand.end()){
            cout << "No playable cards...\n You are forced to draw a card" << endl;
            playerConfirmation();
            drawCards(p, 1);
            cout << "You drew a " << p.hand.back().getName() << "!";
            playerConfirmation();
            
            //checks again if you have a playable card, if not, your turn is over
            it = findPlayableCard(p, card);
            if(it==p.hand.end()){
                cout << "No playable cards drawn... You end your turn." << endl;
                return false;
            }
            input = 2;      //sets input to 2 to account for that player already drew a card at this point
            //If there are playable cards, we exit from loop to decide if we want to play a card or skip
        }
        else{
            cout << "Enter 1 to play a card from hand" << endl;
            cout << "Enter 2 to draw a card from the deck" << endl;
            cin >> input;

            if(input==2){
                drawCards(p, 1);
            }

        }
    }while(!(input == 1 || input == 2));
    
    cout << "\nYour turn: " << endl;
    cout << "Card to Match: " << endl << card.getName() << endl;
    printHand(p);

    if(input == 2){
        cout << "Enter 1 to play a card from hand" << endl;
        cout << "Enter 2 to skip turn" << endl;
        cin >> input;
    }
    if(input == 1){
        cout << "Enter the corresponding number next to your card to play it" << endl;
        cin >> cInd;
        while(checkMatch(*next(p.hand.begin(), cInd-1), card)==false){
            cout << "Unable to play that" << endl;
            cout << "Enter the corresponding number next to your card to play it" << endl;
            cin >> cInd;
        }
        cout << "You played: " << next(p.hand.begin(), cInd-1)->getName() << endl << endl;
        discardPile.push(*next(p.hand.begin(), cInd-1));
        auto it = p.hand.begin();
        advance(it, cInd-1);
        p.hand.erase(it);
        p.handSize--;
        //wildcard actions
        if(checkWild(discardPile.top())==true){
            int c;
            do{
                cout << "Select the color for the wild card: " << endl << endl;
                cout << "Enter 1 for Red\nEnter 2 for Blue\n";
                cout << "Enter 3 for Yellow\nEnter 4 for Green" << endl;
                cin >> c;
            }while(c<1||c>4);
            switch(c){
                case(1):
                    setWildColor(discardPile.top(), "Red");
                    break;
                case(2):
                    setWildColor(discardPile.top(), "Blue");
                    break;
                case(3):
                    setWildColor(discardPile.top(), "Yellow");
                    break;
                case(4):
                    setWildColor(discardPile.top(), "Green");
                    break;
            }
        }
        return true;
    }
    else{
        return false;
    }

    return true;
}

bool Game::npcTurn(Player &p, stack<Card> &discardPile, int playerID){
    Card card = discardPile.top();
    cout << "\nOpponent " << playerID << "'s turn" << endl;
    cout << "Cards in their hands: " << p.handSize << endl;
    cout << "Card to Match: " << endl << card.getName() << endl;
    if(checkWild(card)==true){
        cout << "Wild card color set to: " << card.getColor() << endl;
    }
    auto it = findPlayableCard(p, card);
    //forces npc to draw if no cards are playable
    if(it==p.hand.end()){
        cout << "No playable cards...\nOpponent " << playerID << " is forced to draw a card" << endl;
        drawCards(p, 1);
        
        //checks again if you have a playable card, if not, your turn is over
        it = findPlayableCard(p, card);
        if(it==p.hand.end()){
            cout << "No playable cards drawn...\nOpponent " << playerID << " ends their turn." << endl;
            //end = true;
            return false;
        }
        else{
            cout << it->getName() << " is played!" << endl;
            discardPile.push(*it);
            p.hand.erase(it);
            p.handSize--;
        }
    }
    //actions if npc does have something playable
    else{
        cout << it->getName() << " is played!" << endl;
        discardPile.push(*it);
        p.hand.erase(it);
        p.handSize--;
    }
    if(checkWild(discardPile.top())==true){
        setWildColor(discardPile.top());
    }
    return true;
}
int Game::getNextPlayer(int next, int mod, bool reverse){
    int n = playerCount;
    if(reverse == false){
        next +=mod;
        next %= n;
    }
    else{
        if(next == 0){
            next = n-mod;
        }
        else{
            if(mod==2&&next==1){
                next = n-1;
            }
            next -=mod;
            next %= n;
        }
    }
    return next;
}
list<Card>::iterator Game::findPlayableCard(Player &p, Card card){
    //look for playable cards in hand with iterators and find_if()
    auto it = find_if(p.hand.begin(), p.hand.end(), [&](Card c){
        //checks if player needs to match w/ a nonspecial card, ex a Blue 8, or Red 3
        if(card.special() == false){
            //if current iteration of player hand is non special, compare color and number vals
            if(c.special()==false){
                return c.getColor() == card.getColor() || c.getValue()==card.getValue();
            }
            //else just check if its the same color or a wild card
            else{
                return c.getColor()==card.getColor()||c.getName()=="Wild"||c.getName()=="Wild Draw +4";
            }
        }
        //if the card we are trying to match to is a wild, we simply try to match its chosen color
        else if(checkWild(card)){
            return c.getColor()==card.getColor()||checkWild(c);
        }
        //if it is a skip, reverse, or  draw 2, match with these conditions
        else{
            if(c.special()==false){
                return c.getColor()==card.getColor();
            }
            else{
                return c.getColor() == card.getColor() || c.getValue()==card.getValue()||checkWild(c);
            }
        }
    });
    return it;
}
bool Game::checkWild(Card card){
    if(card.getName()=="Wild"||card.getName()=="Wild Draw +4"){
        return true;
    }
    return false;
}
bool Game::checkSkip(Card card){
    if (card.getName().find("Skip") != string::npos || card.getName().find("+") != string::npos) {
        cout << card.getName() << " causes next player to skip their turn!" << endl;
        return true;
    }
    return false;
}
bool Game::checkReverse(Card card){
    if(card.getName().find("Reverse") != string::npos){
        return true;
    }
    return false;
}
int Game::checkDraw(Card card){
    if(card.getName().find("Draw +2") != string::npos){
        return 2;
    }
    else if(card.getName().find("Draw +4") != string::npos){
        return 4;
    }
    return 0;
}
bool Game::checkWin(Player p, int playerID){
    if(p.handSize==1){
        if(playerID==0){
            cout << "You shout UNO!" << endl;
        }
        else{
            cout << "Opponent " << playerID << " shouts UNO! Uh oh!" << endl;
        }
    }
    else if(p.handSize==0){
        if(playerID==0){
            cout << "Your hand is cleared out and you won the game!" << endl;
        }
        else{
            cout << "Gameover, opponent " << playerID << " wins!" << endl;
        }
        return true;
    }
    return false;
}
void Game::setWildColor(Card &card, string color){
    card.setColor(color);
    cout << "Wild card color set to: " << card.getColor() << endl;
}
void Game::setWildColor(Card &card){
    srand(time(0));
    int n = rand() % 4;
    string color;
    switch (n){
        case(0):
            color = "Red";
            break;
        case(1):
            color = "Blue";
            break;
        case(2):
            color = "Yellow";
            break;
        case(3):
            color = "Green";
            break;
    }
    card.setColor(color);
    cout << "Wild card color set to: " << card.getColor() << endl;
}
//Used to help player keep track of game state
void Game::playerConfirmation(){
    
    string confirm;
    cout << "\n(Enter any key to continue) " << endl;
    cin.ignore();
    getline(cin, confirm);
}
void Game::reshuffle(stack<Card>&discardPile){
    //keeps top card for the discard pile
    Card temp = discardPile.top();
    discardPile.pop();
    /*
    for(int i=0;i<discardPile.size();i++){
        deck.push(discardPile.top());
        discardPile.pop();
    }*/
    while(!discardPile.empty()){
        deck.push(discardPile.top());
        discardPile.pop();
    }
    cout << "Deck is at size: " << deck.getSize() << endl;
            cout << "Discard pile is at: " << discardPile.size() << endl;
    deck.shuffleDeck();
    discardPile.push(temp);
}