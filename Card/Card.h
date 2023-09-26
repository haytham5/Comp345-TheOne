#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//TODO: MAKE DESTRUCTORS
//MAKE EACH DATA VARIABLE A POINTER

class Card {
    public:
        Card(string type);
        void play(); 
        string getType() const;

    private:
        string* type;
};

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