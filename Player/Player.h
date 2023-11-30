#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "../Map/Map.h"  
#include "../LoggingObserver/LoggingObserver.h"
#include "../Orders/Order.h"
#include "../Card/Card.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../PlayerStrategies/PlayerStrategies.h"


using namespace std;

void testPlayers();
class OrdersList;

class Player
{
public:
  // Default constructor
  Player();

  // Parameterized constructor
  Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList);

  // Parameterized constructor with processor
  Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList, CommandProcessor *processor);

   // Parameterized constructor with processor and player strategy
  Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList, CommandProcessor *processor, PlayerStrategy* ps);

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

  vector<Player*>  getAllPlayers();

  // Getter for playerHand
  Hand *getPlayerHand() const;

  void draw();

  void EraseOrder(int i );

  // Setter for playerHand
  void setPlayerHand(Hand *hand);

  void setPlayerStrategy(PlayerStrategy* newStrategy);

  int getReinforcementPool() const;

  void setReinforcementPool(int reinforcementPool);

  void printOrderList();

  // Check if player owns all territories in continent
  bool ownAllTerritoryInContinent();

  OrdersList* getOrderList();

  // Getter for playerTerritories
  vector<Territory *> getPlayerTerritories() const;

  Map* getPlayerMap() const;


  // toDefend() function declaration
  vector<Territory *> toDefend() const;
  
  bool hasCard(const std::string& cardType);
  void setInNegotiationWith(Player* otherPlayer);
  bool isInNegotiationWith(Player* otherPlayer);

  static Player* getPlayerByName(const std::string& name);

  // toAttack() function declaration
  vector<Territory *> toAttack() const;

  void addPlayerTerritories(Territory *territory);

   //issueOrder() function declaration
  void issueOrder(string type);

  // Test State
  void testState(string s);

  // Get Player Command
  void play();

  // Set Player Phase
  void setPhase(string ph);

  // Get Player Phase
  string getPhase();

private:
  PlayerStrategy* ps;
  int reinforcementPool;
  vector<Territory *> playerTerritories;
  Hand *playerHand;
  string playerName;
  OrdersList *orderList;
  Map *map;
  string phase;

  static std::vector<Player*> allPlayers; // Static list of all players


  std::unordered_set<Player*> negotiationPartners;
  // Processor
  CommandProcessor *processor;
};

#endif