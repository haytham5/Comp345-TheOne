#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include "Card.h"
using namespace std;

void testCards() {
    cout << endl << "CREATING CARD AND PLAYING IT:" << endl;

    Card c1("braile");

    c1.play();

    Deck d;
    cout << endl << "DECK AT FIRST:" << endl;
    d.print();

    cout << endl << "ADDING NEW CARD." << endl;
    d.putBack(&c1);

    cout << endl << "DECK AFTER ADD:" << endl;
    d.print();

    cout << endl << "DRAWING CARD." << endl;
    Card* c2 = d.draw();

    cout << endl << "DRAWN TOP CARD:" << endl;
    c2->play();

    cout << endl << "DECK AFTER DRAW" << endl;
    d.print();

    cout << endl << "MAKING HAND" << endl;
    Deck * deckPointer = &d;
    Hand h(deckPointer);

    cout << endl << "DECK SIZE AFTER DRAWING HAND" << endl << d.size();

    cout << endl << "PLAYING CARD FROM HAND" << endl;
    h.play(1);

    cout << endl << "DECK SIZE AFTER PLAYING CARD" << endl << d.size();

    cout << endl << "HAND SIZE AFTER PLAYING CARD" << endl << h.size();

    cout << endl << "DRAWING CARD FROM DECK" << endl;
    h.draw();

    cout << endl << "HAND AFTER DRAWING" << endl;
    h.print();

    cout << endl << "DECK SIZE AFTER DRAWING CARD" << endl << d.size();

    cout << endl << "HAND SIZE AFTER DRAWING CARD" << endl << h.size();
}

int main() {
    
    testCards();

    return 0;
}