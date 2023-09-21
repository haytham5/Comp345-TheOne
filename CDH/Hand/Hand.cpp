#include <string>
#include "../Card/Card.h"
#include "../Deck/Deck.h"
#include "Hand.h"

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

Hand::Hand(Deck *d) {
    deck = d;

    for(int i = 0; i < 7; i++) {
        hand.push_back(deck->draw());
    }

    print();
}

void Hand::play(int i) {
    cout << endl << "Playing card #" << i << endl;

    Card* c = hand[i];

    c->play();

    hand.erase(hand.begin() + i);

    deck->putBack(c);
}

void Hand::draw() {
    hand.push_back(deck->draw());
}


void Hand::print() {
    for (auto elem : hand) {
        elem->play();
    }

}

int Hand::size() {
    return hand.size();
}
