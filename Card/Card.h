#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testCards();

class Card {
    public:
        Card(string type);
        ~Card() {cout << "d ";}
        Card(const Card& c);
        Card& operator = (const Card& c);
        string play(); 
        string getType();
        void print();

        friend ostream & operator << (ostream &out, const Card &object) {
            out << "This is a card of type " << object.type << "." << endl;
            return out;
        }


    private:
        string type;
};

class Deck {
    public: 
        Deck();
        ~Deck() {cout<<"Deleting Deck..."<<endl; for(auto elem : deck) {elem = NULL; delete elem;}}
        Deck(const Deck& d);
        Deck& operator = (const Deck& d);
        void putBack(Card* card);
        Card* draw();
        void print();
        int size();

        friend ostream & operator << (ostream &out, const Deck &object) {
            out << "Deck Contents: " << endl;
            for(auto elem: object.deck) out << *elem;
            return out;
        }
    private:
        vector<Card*> deck;

}; 

class Hand {
    public: 
        Hand(Deck* deck);
        ~Hand() {cout<<"Deleting Hand..."<<endl; for(auto elem : hand) {elem = NULL; delete elem;} }
        Hand(const Hand& h);
        Hand& operator = (const Hand& h);
        string play(int i);
        void draw();
        void print();
        int size();

        friend ostream & operator << (ostream &out, const Hand &object) {
            out << "Hand Contents: " << endl;
            for(auto elem: object.hand) out << *elem;
            return out;
        }
    private:
        Deck* deck;
        vector<Card*> hand;
};


#endif