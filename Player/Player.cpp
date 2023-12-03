#include "Player.h"
#include <iostream>
#include <string>
using namespace std;
// Default constructor
Player::Player()
{
    this->playerName = "";
    this->map = nullptr;
    this->playerHand = nullptr;
    this->orderList = nullptr;
    this->processor = new CommandProcessor('p');
    this->reinforcementPool = 0;
    this->ps=nullptr;
    phase;
}

// Parameterized constructor
Player::Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList)
{
    this->playerName = name;
    this->map = gameMap;
    this->playerHand = hand;
    this->orderList = orderList;
    this->processor = new CommandProcessor('p');
    this->reinforcementPool = 0;
    phase;
}

// Parameterized constructor with processor
Player::Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList, CommandProcessor *processor)
{
    this->playerName = name;
    this->map = gameMap;
    this->playerHand = hand;
    this->orderList = orderList;
    this->processor = processor;
    this->reinforcementPool = 0;
    phase;
}

// Parameterized constructor with processor and player strategy
Player::Player(const string &name, Map *gameMap, Hand *hand, OrdersList *orderList, CommandProcessor *processor, PlayerStrategy *ps)
{
    this->playerName = name;
    this->map = gameMap;
    this->playerHand = hand;
    this->orderList = orderList;
    this->processor = processor;
    this->reinforcementPool = 0;
    phase;
    this->ps=ps;
}

// Copy constructor
Player::Player(const Player &other)
{
    this->playerName = other.playerName;
    this->map = new Map(*other.map);
    this->playerHand = other.playerHand;
    this->orderList = new OrdersList(*other.orderList);
    reinforcementPool = other.reinforcementPool;
}

Player &Player::operator=(const Player &other)
{
    playerTerritories = other.playerTerritories;
    playerHand = other.playerHand;
    playerName = other.playerName;
    orderList = other.orderList;
    reinforcementPool = other.reinforcementPool;
    return *this;
}

// Destructor
Player::~Player()
{
    cout << "Deleting Player: " << endl;
    delete playerHand;
    delete orderList;
    delete ps;
    cout << endl;
}

string Player::getName() const
{
    return playerName;
}

void Player::setName(string name)
{
    this->playerName = name;
}

vector<Player*>  Player::getAllPlayers()
{
    return allPlayers;
}

Hand *Player::getPlayerHand() const
{
    return playerHand;
}

void Player::draw()
{
    playerHand->draw();
}

void Player::EraseOrder(int i)
{
   orderList->erase(i);
}

void Player::setPlayerHand(Hand *hand)
{
    playerHand = hand;
}

void Player::setPlayerStrategy(PlayerStrategy *newStrategy)
{
    if(ps!=nullptr){ 
        delete ps; //Delete previous strategy
    }
    ps= newStrategy;
}

PlayerStrategy* Player::getPlayerStrategy() const {
    return ps;
}

int Player::getReinforcementPool() const
{
    return reinforcementPool;
}

void Player::setReinforcementPool(int modifier)
{
    reinforcementPool += modifier;
}

void Player::printOrderList()
{
    for (auto elem : orderList->getOrders())
    {
        cout << elem->getDescription() << endl;
    }
}

OrdersList* Player::getOrderList()
{
    return orderList;
}

bool Player::ownAllTerritoryInContinent()
{
    return false;
}

vector<Territory *> Player::getPlayerTerritories() const
{
    return playerTerritories;
}

Map *Player::getPlayerMap() const
{
    return this->map;
}

vector<Territory *> Player::toDefend() const
{
    if(ps){
        return ps->toDefend();
    }
    else{
        cout<<"Cannot call toDefend since ps is null"<<endl;
        return vector<Territory*>();
    }
}

vector<Territory *> Player::toAttack() const
{
    if(ps){
        return ps->toAttack();
    }
    else{
        cout<<"Cannot call toAttack since ps is null"<<endl;
        return vector<Territory*>();
    }
}

void Player::addPlayerTerritories(Territory *territory)
{
    playerTerritories.push_back(territory);
}




/*void Player::issueOrder(string type)
{
    Order *order;
    vector<Territory *> toAttackList = toAttack();
    vector<Territory *> toDefendList = toDefend();

    if(reinforcementPool > 0) {
        while (reinforcementPool > 0)
        {
            cout << "Player: " << getName() << " has " << reinforcementPool << " army units available to deploy and has " << toDefendList.size() << " territories \n";

            for (int i = 0; i < toDefendList.size(); i++)
            {
                int deployAmount;
                cout << "How many units would you like to deploy to territory: " << toDefendList[i]->getName() << "?";
                cin >> deployAmount;
                order = new DeployOrder(toDefendList.at(i), deployAmount, playerName);
                reinforcementPool -= deployAmount;
                orderList->addOrder(order);//TODO: delete this line?
            }
        }

        //orderList->addOrder(order);

        Order *order2;

        if (type == "Advance")
        {
            string attackOrDefend;
            cout << "Player: " << getName() << " would you like to move units to defend or attack teritories? Enter Defend or Attack: ";
            cin >> attackOrDefend;
            while (attackOrDefend != "")
            {
                if (attackOrDefend == "Defend")
                {
                    cout << "Player : " << getName() << " your territories are: ";
                    for (int i = 0; i < toDefendList.size(); i++)
                    {
                        cout << toDefendList[i]->getName() << ": " << toDefendList[i]->getArmies() << " army units\n";
                    }
                    string territory1;
                    int territory1Size;
                    string territory2;
                    int numToMove;
                    cout << "Which territory would you like to move army units from?";
                    cin >> territory1;
                    for (int i = 0; i < toDefendList.size(); i++)
                    {
                        if (territory1 == toDefendList[i]->getName())
                        {
                            territory1Size = toDefendList.size();
                        }
                    }
                    cout << "Territory: " << territory1 << " currently has " << territory1Size << " army units\n";
                    cout << "How many army units would you like to move?";
                    cin >> numToMove;
                    cout << "To which territory would you like to send them to?";
                    cin >> territory2;
                    for (int i = 0; i < toDefendList.size(); i++)
                    {
                        if (territory2 == toDefendList[i]->getName())
                        {
                            int armies = numToMove + toDefendList[i]->getArmies();
                            order = new DeployOrder(toDefendList[i], armies, "Player1");
                            cout << "Territory: " << territory2 << " now has " << toDefendList[i]->getArmies() << " army units\n";
                        }
                    }
                    for (int i = 0; i < toDefendList.size(); i++)
                    {
                        if (territory1 == toDefendList[i]->getName())
                        {
                            int armies = toDefendList[i]->getArmies() - numToMove;
                            toDefendList[i]->setArmies(armies);
                        }
                    }
                }
                else if (attackOrDefend == "Attack")
                {
                    cout << "Player : " << getName() << " your territories are: ";
                    for (int i = 0; i < toDefendList.size(); i++)
                    {
                        cout << toDefendList[i]->getName() << ": " << toDefendList[i]->getArmies() << " army units\n";
                    }
                    string territory1;
                    int numToMove;
                    string territory2;
                    cout << "From which territory would you like to move your army units from?";
                    cin >> territory1;
                    Territory *sourceTeritory;
                    for (int i = 0; i < toDefendList.size(); i++)
                    {
                        if (territory1 == toDefendList[i]->getName())
                        {
                            sourceTeritory = toDefendList[i];
                        }
                    }
                    cout << "How many army units from territory " << territory1 << " would you like to move?";
                    cin >> numToMove;
                    cout << "Which of the following neighboring territories would you like to attack? \n";
                    for (int i = 0; i < toAttackList.size(); i++)
                    {
                        cout << toAttackList[i]->getName() << "\n";
                    }
                    cin >> territory2;
                    for (int i = 0; i < toAttackList.size(); i++)
                    {
                        if (territory2 == toAttackList[i]->getName())
                        {
                            const string& c = "Player1";
                            order = new AdvanceOrder(sourceTeritory, toAttackList[i], numToMove, map, c);
                            cout << numToMove << " army units have been advanced to territory " << territory2 << "\n";
                        }
                    }
                }
                else
                {
                    cout << "Invalid command. Try again";
                    cin >> attackOrDefend;
                }
            }
        }

        if (type == "Bomb")
        {
            order2 = new BombOrder();orderList->addOrder(order2);
        }
        else if (type == "Airlift")
        {
            order2 = new AirliftOrder();
            orderList->addOrder(order2);
        }
        else if (type == "Blockade")
        {
            order2 = new BlockadeOrder();
            orderList->addOrder(order2);
        }
        else if(type=="Negotiate"){
            order2 = new NegotiateOrder();
            orderList->addOrder(order2);
        }
        else{
            cout<<"Invalid type in issueOrder(type), no order instance was created."<<endl;
            return;
        }
    }

    else {
        cout << "User has no reinforcements!" << endl;
    }
    
}*/

void Player::issueOrder(string type){
    //Checks to ensure that ps is not nullptr
    if(ps){
        if(type=="Deploy"){
            ps->issueOrder("Deploy");
        }
        else if(type=="Advance"){
            ps->issueOrder("Advance");
        }
        else if(type=="Bomb"){
            ps->issueOrder("Bomb");
        }
        else if(type=="Airlift"){
            ps->issueOrder("Airlift");
        }
        else if(type=="Blockade"){
            ps->issueOrder("Blockade");
        }
        else if(type=="Negotiate"){
            ps->issueOrder("Negotiate");
        }
        else{
            cout<< "Error: Invalid parameter in issueOrder"<<endl;
        }
        
    }
    else{
        cout<< "Cannot call issueOrder since ps is null"<<endl;
    }
}

void Player::testState(string s)
{
    processor->setState(s);
}

void Player::play()
{
    cout << getName() << ", Enter your command: ";
    cin >> *processor;
}

string Player::getPhase()
{
    return phase;
}

std::vector<Player*> Player::allPlayers;

Player* Player::getPlayerByName(const std::string& name) {
    for (Player* player : allPlayers) {
        if (player != nullptr && player->getName() == name) {
            return player;
        }
    }
    return nullptr; // Player not found
}

bool Player::hasCard(const std::string& cardType) {
    return playerHand != nullptr && playerHand->hasCard(cardType);
}

void Player::setInNegotiationWith(Player* otherPlayer) {
    // Add the other player to the negotiation partners set
    negotiationPartners.insert(otherPlayer);
}

bool Player::isInNegotiationWith(Player* otherPlayer) {
    // Check if the other player is in the negotiation partners set
    return negotiationPartners.find(otherPlayer) != negotiationPartners.end();
}

void Player::setPhase(string ph)
{
    phase = ph;
}

// Free function
void testPlayers()
{
    string name1 = "Player 1";
    string name2 = "Player 2";
    Map *map = new Map();
    Deck *deck = new Deck();
    Hand *hand = new Hand(deck);
    Hand *hand2 = new Hand(deck);
    OrdersList *player1OrderList = new OrdersList();
    OrdersList *player2OrderList = new OrdersList();

    Player player1(name1, map, hand, player1OrderList);
    Player player2(name2, map, hand2, player2OrderList);

    // Adding territories to map
    map->addTerritory("TerritoryA", 0, 0, "Continent1");
    map->addTerritory("TerritoryB", 1, 0, "Continent1");
    map->addTerritory("TerritoryC", 2, 0, "Continent2");
    map->addTerritory("TerritoryD", 3, 0, "Continent2");

    // Adding edges
    map->addEdge("TerritoryC", "TerritoryB");

    // Assigning territories to players
    player1.addPlayerTerritories(map->getTerritory("TerritoryA"));
    player1.addPlayerTerritories(map->getTerritory("TerritoryB"));
    player2.addPlayerTerritories(map->getTerritory("TerritoryC"));
    player2.addPlayerTerritories(map->getTerritory("TerritoryD"));

    // Printing out Players' names
    cout << "\nPlayer 1 Name: " << player1.getName() << endl;
    cout << "\nPlayer 2 Name: " << player2.getName() << endl;

    // Printing out Player 1's territories
    cout << "\nPlayer 1's Territories:" << endl;
    vector<Territory *> player1Territories = player1.getPlayerTerritories();
    if (player1Territories.empty())
    {
        cout << "Player 1 has no territories" << endl;
    }
    for (Territory *territory : player1Territories)
    {
        cout << territory->getName() << endl;
    }

    // Printing out Player 2's territories
    cout << "\nPlayer 2's Territories:" << endl;
    vector<Territory *> player2Territories = player2.getPlayerTerritories();
    if (player2Territories.empty())
    {
        cout << "Player 2 has no territories" << endl;
    }
    for (Territory *territory : player2Territories)
    {
        cout << territory->getName() << endl;
    }

    // Calling toDefend() for player 1
    vector<Territory *> territoriesToDefend = player1.toDefend();

    // Calling toAttack() for player 2
    vector<Territory *> territoriesToAttack = player2.toAttack();

    // Showing results for toDefend and toAttack
    cout << "\nPlayer 1 territories to defend: " << endl;
    if (territoriesToDefend.empty())
    {
        cout << "No territories to defend" << endl;
    }
    for (Territory *territory : territoriesToDefend)
    {
        cout << territory->getName() << endl;
    }

    cout << "\nPlayer 2 territories to attack: " << endl;
    if (territoriesToAttack.empty())
    {
        cout << "No territories to attack" << endl;
    }
    for (Territory *territory : territoriesToAttack)
    {
        cout << territory->getName() << endl;
    }

    // Printing player 1's hand
    cout << "\n"
         << player1.getName() << "'s hand:" << endl;
    player1.getPlayerHand()->print();

    // Printing player 2's hand
    cout << "\n"
         << player2.getName() << "'s hand:" << endl;
    player2.getPlayerHand()->print();

    // Calling issue order player 1 and player 2 to add orders to their orderlist

    cout << "\nPlayer 1 is playing: " << endl;
    player1.issueOrder(player1.getPlayerHand()->play(0));
    cout << "\n" << player1.getName() << "'s hand:" << endl;
    player1.getPlayerHand()->print();

    player1.issueOrder(player1.getPlayerHand()->play(1));
    cout << "\n" << player1.getName() << "'s hand:" << endl;
    player1.getPlayerHand()->print();




    cout << "\nPlayer 2 is playing: " << endl;
    player2.issueOrder(player2.getPlayerHand()->play(0));
    cout << "\n"
         << player2.getName() << "'s hand:" << endl;
    player2.getPlayerHand()->print();
    
    player2.issueOrder(player2.getPlayerHand()->play(1));
    cout << "\n"
         << player2.getName() << "'s hand:" << endl;
    player2.getPlayerHand()->print();



    // Print out player 1's and 2's orderLists
    cout << "\nPlayer 1's order list:" << endl;
    player1.printOrderList();
    cout << "\nPlayer 2's order list:" << endl;
    player2.printOrderList();

    cout << endl;
    delete map;
    cout << endl;
    delete deck;
    cout << endl;
}

ostream &operator<<(ostream &out, const Player &object)
{
    out << "Player Attributes:" << endl
        << "Name: " << object.playerName << endl
        << "Hand: " << *object.playerHand << endl
        << "Orders: " << *object.orderList << endl;
    return out;
}