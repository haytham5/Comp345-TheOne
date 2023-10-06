#include "Player.h"
using namespace std;
//Default constructor
Player::Player(){
    this->playerName="";
    this->map=nullptr;
    this->playerHand=nullptr;
    this->orderList=nullptr;
}

//Parameterized constructor
Player::Player(const string& name, Map* gameMap, Hand* hand, OrdersList* orderList){
    this->playerName=name;
    this->map=gameMap;
    this->playerHand=hand;
    this->orderList=orderList;
}

//Copy constructor
Player::Player(const Player& other) {
    this->playerName = other.playerName;
    this->map = new Map(*other.map);
    this->playerHand = other.playerHand;
    this->orderList= new OrdersList(*other.orderList);
}

//Destructor
Player:: ~Player(){
    delete map;
    delete playerHand;
    delete orderList;
}

string Player::getName() const{
    return playerName;
}

void Player::setName(string name){
    this->playerName=name;   
}

Hand* Player::getPlayerHand() const {
    return playerHand;
}

void Player::setPlayerHand(Hand* hand) {
    playerHand = hand;
}

void Player::printOrderList(){
    for(auto elem: orderList){
        cout<<elem->getDescription()<<endl;
    }
}

vector<Territory*> Player::getPlayerTerritories() const{
    return playerTerritories;
}

//Returns arbitrary list of territories to defend (in this case, I made it defend all territories owned ny the player)
vector<Territory*> Player::toDefend() const {

   vector<Territory*> territoriesToDefend;//Create empty vector
    for(int i=0;i<playerTerritories.size();i++){
        territoriesToDefend.push_back(playerTerritories[i]);
    }
    return territoriesToDefend;

}

//Returns arbitrary list of territories to attack
vector<Territory*> Player::toAttack() const{
    vector<Territory*> territoriesToAttack;//Create empty vector
    for(int i=0;i<playerTerritories.size();i++){
       vector<string> neighbours= map->getNeighbors(playerTerritories[i]->getName());
       for(int j=0;j<neighbours.size();j++){
        if(map->getTerritory(neighbours[i])->getPlayer()!=this->playerName){
            territoriesToAttack.push_back(map->getTerritory(neighbours[i]));
        }
       }
    }
    return territoriesToAttack;
}

void Player::addPlayerTerritories(Territory *territory)
{
    playerTerritories.push_back(territory);
}

void Player::issueOrder(string type){
    Order* order;

    if(type=="Deploy"){
        order=new DeployOrder();
    }
    else if(type=="Bomb"){
        order= new BombOrder();
    }
    else if(type=="Advance"){
        order= new AdvanceOrder();
    }
    else if(type=="Airlift"){
        order= new AirliftOrder();
    }
    else if(type=="Blockade"){
        order=new BlockadeOrder();
    }
    else{
        return;
    }

    orderList->addOrder(order);
}
