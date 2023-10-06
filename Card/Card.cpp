#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;
#include "Card.h"

Card::Card(string t) {
    type = t;
}

string Card::play()
{
    print();
    return type;
}

string Card::getType()
{
    return type;
}

void Card::print()
{
    cout << "This is a card of type " << getType() << "." << endl;
}

Deck::Deck()
{
    srand((unsigned) time(NULL));

    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

    for(int i = 0; i < 52; i++) {
        Card * c = new Card(types[rand() % 5]);
        deck.push_back(c);
    }

    cout << "Hand successfully created." << endl;
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
    for (auto elem : deck) elem->print();
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

    cout << "Hand successfully created." << endl;
}

string Hand::play(int i) {
    cout << endl << "Playing card #" << i << endl;

    Card* c = hand[i];

    string type = c->play();

    hand.erase(hand.begin() + i);

    deck->putBack(c);

    return type;
}

void Hand::draw() {
    hand.push_back(deck->draw());
}


void Hand::print() {
    for (auto elem : hand) elem->print();
}

int Hand::size() {
    return hand.size();
}
