#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
#include "Card.h"

Card::Card(string t) {
    type = &t;
}

void Card::play()
{
    cout << "Playing card of type " << getType() << "." << endl;

    //TODO ADD IT TO PLAYER ORDER
}

string Card::getType() const
{
    //SEGMENTATION FAULT MIGHT START AT  LINE 35
    cout << *type;
    return *type;
}


Deck::Deck()
{
    srand((unsigned) time(NULL));

    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

    for(int i = 0; i < 52; i++) {
        string s = types[rand() % 5];
        Card c(types[rand() % 5]);
        Card* cptr = &c;
        deck.push_back(cptr);
    }
}

void Deck::putBack(Card *card)
{
    deck.insert(deck.begin(), card);

    cout << "Card put back in deck." << endl;
}

Card *Deck::draw()
{
    Card *c = deck.back();
    deck.pop_back();
    return c;
}

void Deck::print()
{
    for (auto elem : deck) {
        elem->play();
    }

}

int Deck::size()
{
    return deck.size();
}

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
