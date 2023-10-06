#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

#include "Card.h"

// CARD CLASS
Card::Card(string t) {
    type = t;
}

Card::Card(const Card &c)
{
    type = c.type;
}

Card &Card::operator=(const Card &c)
{
    type = c.type;
    return *this;
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

// Function to print information about the card
void Card::print()
{
    cout << "This is a card of type " << getType() << "." << endl;
}

// DECK CLASS
Deck::Deck()
{
    srand((unsigned) time(NULL));

    // Array of possible card types
    string types[5] = {"Bomb", "Airlift", "Blockade", "Deploy", "Advance"};

    // Create 52 cards with random types and add them to the deck
    for(int i = 0; i < 52; i++) {
        Card * c = new Card(types[rand() % 5]);
        deck.push_back(c);
    }

    cout << "Deck successfully created." << endl;
}

Deck::Deck(const Deck &d)
{
    deck = d.deck;
}

Deck &Deck::operator=(const Deck &d)
{
    deck = d.deck;
    return *this;
}

// Function to put a card back into the deck
void Deck::putBack(Card *card)
{
    deck.insert(deck.begin(), card);

    cout << "Card put back in deck." << endl;
}

// Function to draw a card from the deck
Card *Deck::draw()
{
    Card *c = deck.back();
    deck.pop_back();
    return c;
}

// Function to print the contents of the deck
void Deck::print()
{        
    for (auto elem : deck) elem->print();
}

// Function to get the size of the deck
int Deck::size()
{
    return deck.size();
}

// HAND CLASS
Hand::Hand(Deck *d) {
    deck = d;

    // Draw 7 cards from the deck to initialize the hand
    for(int i = 0; i < 7; i++) {
        hand.push_back(deck->draw());
    }

    cout << "Hand successfully created." << endl;
}

Hand::Hand(const Hand &h)
{
    hand = h.hand;
    deck = h.deck;
}

Hand &Hand::operator=(const Hand &h)
{
    hand = h.hand;
    deck = h.deck;
    return *this;
}

string Hand::play(int i)
{
    cout << endl << "Playing card #" << i << endl;

    // Play the desired card
    Card* c = hand[i];

    string type = c->play();

    // Remove the played card from the hand
    hand.erase(hand.begin() + i);

    // Put the played card back into the deck
    deck->putBack(c);

    return type;
}

// Function to draw a card from the deck and add it to the hand
void Hand::draw() {
    hand.push_back(deck->draw());
}

// Function to print the contents of the hand
void Hand::print() {
    cout<<"Printing hand: "<<endl;
    for (auto elem : hand) elem->print();
}

// Function to get the size of the hand
int Hand::size() {
    return hand.size();
}

// Function to test the Card, Deck, and Hand classes
void testCards() {
    cout << endl << "CREATING CARD AND PRINTING IT:" << endl;

    string s = "braile";

    Card * c1 = new Card(s);

    c1->play();

    Deck * d = new Deck();
    cout << endl << "DECK AT FIRST:" << endl;
    d->print();

    cout << endl << "ADDING NEW CARD." << endl;
    d->putBack(c1);

    cout << endl << "DECK AFTER ADD:" << endl;
    d->print();

    cout << endl << "DRAWING CARD." << endl;
    Card* c2 = d->draw();

    cout << endl << "DRAWN TOP CARD:" << endl;
    c2->play();

    cout << endl << "DECK AFTER DRAW" << endl;
    d->print();

    cout << endl << "MAKING HAND" << endl;
    Hand * h = new Hand(d);

    cout << endl << "DECK SIZE AFTER DRAWING HAND" << endl << d->size();

    cout << endl << "PLAYING CARD FROM HAND" << endl;
    h->play(1);

    cout << endl << "DECK SIZE AFTER PLAYING CARD" << endl << d->size();

    cout << endl << "HAND SIZE AFTER PLAYING CARD" << endl << h->size();

    cout << endl << "DRAWING CARD FROM DECK" << endl;
    h->draw();

    cout << endl << "HAND AFTER DRAWING" << endl;
    h->print();

    cout << endl << "DECK SIZE AFTER DRAWING CARD" << endl << d->size();

    cout << endl << "HAND SIZE AFTER DRAWING CARD" << endl << h->size() << endl;

    delete d; // C1 and C2 are already deleted by d
    delete h;
}