#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
#include "../Map/Map.h"
#include "../Orders/Order.h"
#include "../Card/Card.h"

using namespace std;

class Player{
 public:

   //Default constructor
    Player();

   //Parameterized constructor
    Player(const string& name, Map* gameMap, Hand* hand, OrdersList* orderList);
    
    //Copy constructor
    Player(const Player& other);

    //Destructor
    ~Player();

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
    void issueOrder(string type);

 private:
   vector<Territory*> playerTerritories;
    Hand* playerHand;
    string playerName;
    OrdersList* orderList;
    Map* map;

};

#endif