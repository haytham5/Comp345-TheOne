#include <string>
#include "../Card/Card.h"
#include "Deck.h"

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Card;
Deck::Deck()
{
    srand((unsigned) time(NULL));

    string types[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

    for(int i = 0; i < 52; i++) {
        Card *c = new Card(types[rand() % 5]);
        deck.push_back(c);
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
