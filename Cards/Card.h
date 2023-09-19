#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card {
    public:
        Card(string type);
        void play(); 
        string getType() const;

    private:
        string type;
};


#endif