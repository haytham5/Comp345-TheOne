#include "Player.h"
using namespace std;
//Default constructor
Player::Player(){

}

//Parameterized constructor
Player::Player(const string& name, Map* gameMap, Hand* hand/*, vector<Order*> orderList*/){
    this->playerName=name;
    this->map=gameMap;
    //this->playerTerritories=new vector<Territory*>;//gameMap->getTerritoriesByName(name);
    this->playerHand=hand;
    //this->orderList=orderList;
}

//Copy constructor (CHECK)
Player::Player(const Player& other) {
    this->playerName = other.playerName;
    this->map = new Map(*other.map);
    this->playerHand = other.playerHand;
    //TODO COPY ORDERLIST AS WELL
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


//void Player::issueOrder(Order* order){
    //TODO
//}