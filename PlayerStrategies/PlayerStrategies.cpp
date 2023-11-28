#include "PlayerStrategies.h"
using namespace std;

//PLAYER STRATEGY
PlayerStrategy::PlayerStrategy(){
    //No additional logic needed here
}
PlayerStrategy::PlayerStrategy(Player *player) : p(player){}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &other) : p(other.p){}

PlayerStrategy::~PlayerStrategy(){
    //No additional logic needed here
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& other) {
    if (this!= &other) {
        p= other.p;
    }
    return *this;
}

ostream &operator<<(ostream &out, const PlayerStrategy &playerStrategy){
    //If p is not null, print information using Player's stream insertion operator
    if (playerStrategy.p) {
        out << "PlayerStrategy (using Player's information): " << *(playerStrategy.p);
    } else {
        out << "PlayerStrategy (null pointer)";
    }
    return out;
}

//HUMAN PLAYER
HumanPlayer::HumanPlayer(Player *player) : PlayerStrategy(player){}

HumanPlayer::HumanPlayer(const HumanPlayer &other) : PlayerStrategy(other){}

HumanPlayer::~HumanPlayer(){

}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer& other) {
    if (this!= &other) {
        PlayerStrategy::operator=(other);
    }
    return *this;
}

ostream &operator<<(ostream &out, const HumanPlayer &humanPlayer){
    //If p is not null, print information using Player's stream insertion operator
    if (humanPlayer.p) {
        out << "HumanPlayer (using Player's information): " << *(humanPlayer.p);
    } else {
        out << "HumanPlayer (null pointer)";
    }
    return out;
}

void HumanPlayer::issueOrder(string type){
    //TODO
    Order *order;
    vector<Territory *> toAttackList = toAttack();
    vector<Territory *> toDefendList = toDefend();
    if(type=="Deploy"){

    }
    else if(type=="Advance"){

    }
}

vector<Territory *> HumanPlayer::toDefend(){
    //TODO
}

vector<Territory *> HumanPlayer::toAttack(){
    //TODO
}

//AGGRESSIVE PLAYER
AggressivePlayer::AggressivePlayer(Player *player) : PlayerStrategy(player){}

AggressivePlayer::AggressivePlayer(const AggressivePlayer& other) : PlayerStrategy(other) {}

AggressivePlayer::~AggressivePlayer(){

}

AggressivePlayer& AggressivePlayer::operator=(const AggressivePlayer& other) {
    if (this!= &other) {
        PlayerStrategy::operator=(other);
    }
    return *this;
}

ostream &operator<<(ostream &out, const AggressivePlayer &aggressivePlayer){
    //If p is not null, print information using Player's stream insertion operator
    if (aggressivePlayer.p) {
        out << "AggressivePlayer (using Player's information): " << *(aggressivePlayer.p);
    } else {
        out << "AggressivePlayer (null pointer)";
    }
    return out;
}

void AggressivePlayer::issueOrder(string type){
    //TODO
}

vector<Territory *> AggressivePlayer::toDefend(){
    //Aggressive Player does NOT defend
    return vector<Territory*>();
}

//Returns all neighbouring territories since aggressive player always advances until it cannot anymore
vector<Territory *> AggressivePlayer::toAttack(){
    vector<Territory *> territoriesToAttack; // Create empty vector
    vector<Territory*> playerTerritories=p->getPlayerTerritories();
    string playerName=p->getName();
    Map* map=p->getPlayerMap();
    for (int i = 0; i < playerTerritories.size(); i++)
    {
        vector<string> neighbours = map->getNeighbors(playerTerritories.at(i)->getName());
        for (int j = 0; j < neighbours.size(); j++)
        {
            if (map->getTerritory(neighbours[j])->getPlayer() != playerName)
            {
                territoriesToAttack.push_back(map->getTerritory(neighbours[j]));
            }
        }
    }
    return territoriesToAttack;
}

//BENEVOLENT PLAYER
BenevolentPlayer::BenevolentPlayer(Player *player) : PlayerStrategy(player){}

BenevolentPlayer::BenevolentPlayer(const BenevolentPlayer& other) : PlayerStrategy(other) {}

BenevolentPlayer::~BenevolentPlayer(){

}

BenevolentPlayer& BenevolentPlayer::operator=(const BenevolentPlayer& other) {
    if (this!= &other) {
        PlayerStrategy::operator=(other);
    }
    return *this;
}

ostream &operator<<(ostream &out, const BenevolentPlayer &benevolentPlayer){
    //If p is not null, print information using Player's stream insertion operator
    if (benevolentPlayer.p) {
        out << "BenevolentPlayer (using Player's information): " << *(benevolentPlayer.p);
    } else {
        out << "BenevolentPlayer (null pointer)";
    }
    return out;
}

void BenevolentPlayer::issueOrder(string type){
    //TODO
}

//Returns the weakest territory owned by the player
vector<Territory *> BenevolentPlayer::toDefend(){
    vector<Territory *> territoriesToDefend; //Creates empty vector
    vector<Territory *> playerTerritories = p->getPlayerTerritories();
    
    //Finding the weakest territory
    Territory* weakestTerritory = nullptr;
    int minArmies = numeric_limits<int>::max();//Setting minArmies to max int

    for (Territory* territory : playerTerritories) {
        int territoryArmies = territory->getArmies();
        if (territoryArmies < minArmies) {
            minArmies = territoryArmies;
            weakestTerritory = territory;
        }
    }

    //If a weakest territory is found, add it to the vector
    if (weakestTerritory != nullptr) {
        territoriesToDefend.push_back(weakestTerritory);
    }

    return territoriesToDefend;
}

vector<Territory *> BenevolentPlayer::toAttack(){
    //Benevolent player does NOT attack
    return vector<Territory*>();
}

// NEUTRAL PLAYER
NeutralPlayer::NeutralPlayer(Player *player) : PlayerStrategy(player){}

NeutralPlayer::NeutralPlayer(const NeutralPlayer& other) : PlayerStrategy(other) {}

NeutralPlayer::~NeutralPlayer(){

}

NeutralPlayer& NeutralPlayer::operator=(const NeutralPlayer& other) {
    if (this!= &other) {
        PlayerStrategy::operator=(other);
    }
    return *this;
}

ostream &operator<<(ostream &out, const NeutralPlayer &neutralPlayer){
    //If p is not null, print information using Player's stream insertion operator
    if (neutralPlayer.p) {
        out << "NeutralPlayer (using Player's information): " << *(neutralPlayer.p);
    } else {
        out << "NeutralPlayer (null pointer)";
    }
    return out;
}

void NeutralPlayer::issueOrder(string type){
    //TODO
}

vector<Territory *> NeutralPlayer::toDefend(){
    //TODO
}

vector<Territory *> NeutralPlayer::toAttack(){
    //TODO
}

//CHEATER PLAYER
CheaterPlayer::CheaterPlayer(Player *player) : PlayerStrategy(player){}

CheaterPlayer::CheaterPlayer(const CheaterPlayer& other) : PlayerStrategy(other) {}

CheaterPlayer::~CheaterPlayer(){

}

CheaterPlayer& CheaterPlayer::operator=(const CheaterPlayer& other) {
    if (this!= &other) {
        PlayerStrategy::operator=(other);
    }
    return *this;
}

ostream &operator<<(ostream &out, const CheaterPlayer &cheaterPlayer){
    //If p is not null, print information using Player's stream insertion operator
    if (cheaterPlayer.p) {
        out << "CheaterPlayer (using Player's information): " << *(cheaterPlayer.p);
    } else {
        out << "CheaterPlayer (null pointer)";
    }
    return out;
}

void CheaterPlayer::issueOrder(string type){
    //TODO
}

vector<Territory *> CheaterPlayer::toDefend(){
    //TODO
}

vector<Territory *> CheaterPlayer::toAttack(){
    //TODO
}

//Free function
void testPlayerStrategies(){
    //TODO
}

