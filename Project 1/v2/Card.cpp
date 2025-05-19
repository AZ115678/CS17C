#include "Card.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
Card::Card(){
    
}
Card::Card(string color, int value){
    this->color = color;
    this->value = value;
    name = color + " " + to_string(value);
}

Card::Card(string name, int value, bool isSpecial){
    this->name = name;
    this->value = value;
    this->isSpecial = isSpecial;
}
Card::Card(string name, string color, int value, bool isSpecial){
    this->color = color;
    this->name = color + " " + name;
    this->value = value;
    this->isSpecial = isSpecial;
}