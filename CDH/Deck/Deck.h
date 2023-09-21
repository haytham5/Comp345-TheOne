#ifndef DECK_H
#define DECK_H

#include <string>
#include <vector>
#include "../Card/Card.h"

using namespace std;

class Card;
class Deck {
    public: 
        Deck();
        void putBack(Card* card);
        Card* draw();
        void print();
        int size();
    private:
        vector<Card*> deck;

};


#endif