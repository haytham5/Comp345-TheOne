#ifndef HAND_H
#define HAND_H

#include <string>
#include <vector>
#include "../Card/Card.h"

class Card;
class Deck;
class Hand {
    public: 
        Hand(Deck* deck);
        void play(int i);
        void draw();
        void print();
        int size();
    private:
        Deck* deck;
        vector<Card*> hand;
};


#endif