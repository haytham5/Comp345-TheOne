#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
#include"Map.h"
//#include"Orders.h"
#include"Card.h"

using namespace std;

class Player{
 public:

   //Default constructor
    Player();

   //Parameterized constructor
    Player(const string& name, Map* gameMap, Hand* hand/*, vector<Order*> orderList*/);
    
    //Copy constructor
    Player(const Player& other);

    //Getter for playerName
    string getName() const;

    //Setter for playerName
    void setName(string name);

   //Getter for playerHand
    Hand* getPlayerHand() const;

    //Setter for playerHand
    void setPlayerHand(Hand* hand);

    //Getter for playerTerritories
    vector<Territory*> getPlayerTerritories() const;

    //toDefend() function declaration
    vector<Territory*> toDefend() const;

    //toAttack() function declaration
    vector<Territory*> toAttack() const;

    void addPlayerTerritories(Territory* territory);
    
    //issueOrder() function declaration
    //void issueOrder(Order* order);

 private:
   vector<Territory*> playerTerritories;
    Hand* playerHand;
    string playerName;
    //vector<Order*> orderList;
    Map* map;

};

#endif