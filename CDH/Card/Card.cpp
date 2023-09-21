#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
using namespace std;
#include "Card.h"

Card::Card(string t) {
    type = t;
}

void Card::play()
{
    cout << "Playing card of type " << getType() << "." << endl;

    //TODO ADD IT TO PLAYER ORDER
}

string Card::getType() const
{
    return type;
}
