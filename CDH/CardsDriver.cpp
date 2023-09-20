#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include "Card/Card.h"
#include "Deck/Deck.h"
#include "CardsDriver.h"
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

    //CREATE HAND

    //PLAY CARDS
}