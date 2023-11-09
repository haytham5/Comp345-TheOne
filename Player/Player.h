#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../Orders/Order.h"
#include "../Card/Card.h"
#include "../CommandProcessing/CommandProcessing.h"

using namespace std;

void testPlayers();

class Player
{
public:
  // Default constructor
  Player();

  // Parameterized constructor
  Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList);

  // Parameterized constructor with processor
  Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList, CommandProcessor *processor);

  // Copy constructor
  Player(const Player &other);

  // Operator
  Player &operator=(const Player &other);

  // Ostream
  friend ostream &operator<<(ostream &out, const Player &object);

  // Destructor
  ~Player();

  // Getter for playerName
  string getName() const;

  // Setter for playerName
  void setName(string name);

  // Getter for playerHand
  Hand *getPlayerHand() const;

  // Setter for playerHand
  void setPlayerHand(Hand *hand);

  void printOrderList();

  // Getter for playerTerritories
  vector<Territory *> getPlayerTerritories() const;

  // toDefend() function declaration
  vector<Territory *> toDefend() const;

  // toAttack() function declaration
  vector<Territory *> toAttack() const;

  void addPlayerTerritories(Territory *territory);

  // issueOrder() function declaration
  void issueOrder(string type);

  // Get Player Order List
  OrdersList *getOrderList();

  // Test State
  void testState(string s);

  // Get Player Command
  void play();

  // Set Player Phase
  void setPhase(string ph);

  // Get Player Phase
  string getPhase();

  // Check if player owns all territories in continent
  bool ownAllTerritoryInContinent();

private:
  vector<Territory *> playerTerritories;
  Hand *playerHand;
  string playerName;
  OrdersList *orderList;
  Map *map;
  string phase;

  // Processor
  CommandProcessor *processor;
};

#endif