#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// testCards declaration
void testCards();

// Card class
class Card {
public:
    // Constructor
    Card(string type);

    // Destructor
    ~Card() {};

    // Copy constructor
    Card(const Card& c);

    // Assignment operator
    Card& operator=(const Card& c);

    // Play a card
    string play();

    // Get card type
    string getType();

    // Print
    void print();

    // Ostream
    friend ostream& operator<<(ostream& out, const Card& object) {
        out << "This is a card of type " << object.type << "." << endl;
        return out;
    }

private:
    string type;
};

// Deck class
class Deck {
public:
    // Constructor
    Deck();

    // Destructor 
    ~Deck() {
        cout << "Deleting Deck..." << endl;
        for (auto elem : deck) {
            elem = NULL;
            delete elem;
        }
    }

    // Copy constructor 
    Deck(const Deck& d);

    // Assignment operator 
    Deck& operator=(const Deck& d);

    // Function to put a card back into the deck
    void putBack(Card* card);

    // Function to draw a card from the deck
    Card* draw();

    // Function to print the contents of the deck
    void print();

    // Function to get the size of the deck
    int size();

    // Ostream
    friend ostream& operator<<(ostream& out, const Deck& object) {
        out << "Deck Contents: " << endl;
        for (auto elem : object.deck)
            out << *elem;
        return out;
    }

private:
    vector<Card*> deck;
};

// Hand class
class Hand {
public:
    // Constructor
    Hand(Deck* deck);

    // Destructor
    ~Hand() {
        cout << "Deleting Hand..." << endl;
        for (auto elem : hand) {
            elem = NULL;
            delete elem;
        }
    }

    // Copy constructor
    Hand(const Hand& h);

    // Assignment operator
    Hand& operator=(const Hand& h);

    // Function to play a card from the hand
    string play(int i);

    // Function to draw a card from the deck and add it to the hand
    void draw();

    // Function to print the contents of the hand
    void print();

    // Function to get the size of the hand
    int size();

    // Ostream
    friend ostream& operator<<(ostream& out, const Hand& object) {
        out << "Hand Contents: " << endl;
        for (auto elem : object.hand)
            out << *elem;
        return out;
    }

private:
    Deck* deck;
    vector<Card*> hand;
};

#endif