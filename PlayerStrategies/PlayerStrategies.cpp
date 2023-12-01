#include "PlayerStrategies.h"
#include<random>
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
    Order *order;
    vector<Territory *> toAttackList = toAttack();
    vector<Territory *> toDefendList = toDefend();
    int reinforcementPool=p->getReinforcementPool();
    OrdersList* orderList=p->getOrderList();
    Map* map=p->getPlayerMap();
    if(type=="Deploy"){
        if(reinforcementPool> 0) {
            while (reinforcementPool > 0)
            {
                cout << "Player: " << p->getName() << " has " << reinforcementPool << " army units available to deploy and has " << toDefendList.size() << " territories \n";

                for (int i = 0; i < toDefendList.size(); i++)
                {
                    int deployAmount;
                    cout << "How many units would you like to deploy to territory: " << toDefendList[i]->getName() << "?";
                    cin >> deployAmount;
                    order = new DeployOrder(toDefendList.at(i), deployAmount, p->getName());
                    reinforcementPool -= deployAmount;
                    orderList->addOrder(order);//TODO: delete this line?
                }
            }
        }
        else {
            cout << "User has no reinforcements!" << endl;
        }
    }
        //orderList->addOrder(order);TODO Uncomment this?

    if (type == "Advance")//TODO, add reinforcement pool?
    {
        string attackOrDefend;
        cout << "Player: " << p->getName() << " would you like to move units to defend or attack teritories? Enter Defend or Attack: ";
        cin >> attackOrDefend;
        while (attackOrDefend != "")
        {
            if (attackOrDefend == "Defend")
            {
                cout << "Player : " << p->getName() << " your territories are: ";
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
                cout << "Player : " << p->getName() << " your territories are: ";
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
        //TODO
        order = new BombOrder();
        p->getOrderList()->addOrder(order);
    }
    else if (type == "Airlift")
    {
        //TODO (with reinforcement pool?)
        order = new AirliftOrder();
        orderList->addOrder(order);
    }
    else if (type == "Blockade")
    {
        //TODO
        order = new BlockadeOrder();
        orderList->addOrder(order);
    }
    else if(type=="Negotiate"){
        //TODO
        order = new NegotiateOrder();
        orderList->addOrder(order);
    }
    else{
        cout<<"Invalid type in issueOrder(type), no order instance was created."<<endl;
        return;
    }
}

    

//Returns all territories owned by player
vector<Territory *> HumanPlayer::toDefend(){
    vector<Territory *> playerTerritories=p->getPlayerTerritories();
    vector<Territory *> territoriesToDefend; // Create empty vector
    for (int i = 0; i < playerTerritories.size(); i++)
    {
        territoriesToDefend.push_back(playerTerritories[i]);
    }
    return territoriesToDefend;
}

vector<Territory *> HumanPlayer::toAttack(){
    vector<Territory *> playerTerritories=p->getPlayerTerritories();
    vector<Territory *> territoriesToAttack; // Create empty vector
    Map* map=p->getPlayerMap();
    for (int i = 0; i < playerTerritories.size(); i++)
    {
        vector<string> neighbours = map->getNeighbors(playerTerritories.at(i)->getName());
        for (int j = 0; j < neighbours.size(); j++)
        {
            if (map->getTerritory(neighbours[j])->getPlayer() != p->getName())
            {
                territoriesToAttack.push_back(map->getTerritory(neighbours[j]));
            }
        }
    }
    return territoriesToAttack;
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
    Order *order;
    int reinforcementPool = p->getReinforcementPool();
    OrdersList *orderList = p->getOrderList();
    Map *map = p->getPlayerMap();

    if(type=="Deploy"){
        vector<Territory *> toAttackList = toAttack();
        vector<Territory *> toDefendList = toDefend();
        if (reinforcementPool > 0) {
            while (reinforcementPool > 0) {
                // Aggressive player deploys armies on its strongest country
                Territory *strongestTerritory = toDefendList.front(); 
                int deployAmount = reinforcementPool;
                order = new DeployOrder(strongestTerritory, deployAmount, p->getName());
                reinforcementPool -= deployAmount;
                orderList->addOrder(order);
            } 
        }
        else {
        cout << "User has no reinforcements!" << endl;
        }
    }

    if(type=="Advance"){
        vector<Territory *> toAttackList = toAttack();
        vector<Territory *> toDefendList = toDefend();
        //Aggressive player always advances to enemy territories until it cannot do so anymore
        for (Territory *sourceTerritory : toDefendList) {
            for (Territory *targetTerritory : toAttackList) {
                if(sourceTerritory->getArmies()>0){
                    order = new AdvanceOrder(sourceTerritory, targetTerritory, sourceTerritory->getArmies(), map, p->getName());
                    orderList->addOrder(order);
                }
                else{
                    cout<<"Source territory has no armies"<<endl;
                }
            }
        }
    }
    else if(type=="Bomb"){
        //Aggressive player bombs a random enemy territory in toAttackList
        vector<Territory *> toAttackList = toAttack();
        if (!toAttackList.empty()) {
            //Generate a random index within the toAttackList vector
            random_device rd;
            mt19937 gen(rd());//Mersenne twister PRNG with random seed
            uniform_int_distribution<> dis(0, toAttackList.size() - 1);
            int randomIndex = dis(gen);

            //Get the random enemy territory
            Territory *targetTerritory = toAttackList[randomIndex];

            //Create and add the BombOrder
            Order *order = new BombOrder(targetTerritory, p->getName(), map);
            orderList->addOrder(order);
        } 
        else {
            cout << "No enemy territories to bomb." << endl;
        }
    }
    else if(type=="Airlift"){//Armies are already checked in the execute() method, so no need to check armies here
        //Randomly select a source territory for the AirliftOrder
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> sourceDistribution(0, p->getPlayerTerritories().size() - 1);
        Territory *sourceTerritory = p->getPlayerTerritories().at(sourceDistribution(gen));

        // Move armies from source to the front of toDefendList using AirliftOrder
        int airliftArmies = sourceTerritory->getArmies() / 2;  // Move half of the armies
        Territory *targetTerritory = toDefend().front();
        order = new AirliftOrder(sourceTerritory, targetTerritory, airliftArmies, p->getName());
        orderList->addOrder(order);
    }
    else if(type=="Blockade"){
        //Get the strongest territory owned by the player
        vector<Territory*> toDefendList = toDefend();
        if (!toDefendList.empty()) {
            Territory* targetTerritory = toDefendList.front();

            //Create and add the BlockadeOrder to the order list
            order = new BlockadeOrder(targetTerritory, p->getName());
            orderList->addOrder(order);
        } 
        else {
            cout << "Blockade order is invalid. No territories to defend." << endl;
        }
    }
    else if(type=="Negotiate"){
        //Randomly select a target player for the NegotiateOrder
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> playerDistribution(0, p->getAllPlayers().size() - 1);
        string targetPlayer = p->getAllPlayers().at(playerDistribution(gen))->getName();

        //Create and add the NegotiateOrder to the order list
        order = new NegotiateOrder(p->getName(), targetPlayer);
        orderList->addOrder(order);
    }
}
    

//Returns strongest territory owned by Player
vector<Territory *> AggressivePlayer::toDefend(){
     vector<Territory *> territoriesToDefend; //Creates empty vector
    vector<Territory*> playerTerritories=p->getPlayerTerritories();

    int maxArmies = -1;
    Territory *strongestTerritory = nullptr;

    for (Territory* territory : playerTerritories) {
        int territoryArmies = territory->getArmies();
        if (territoryArmies > maxArmies) {
            maxArmies = territoryArmies;
            strongestTerritory = territory;
        }
    }

    //If a strongest territory is found, add it to the vector
    if (strongestTerritory != nullptr) {
        territoriesToDefend.push_back(strongestTerritory);
    }

    return territoriesToDefend;
}

//Returns all neighbouring territories since aggressive player always advances until it cannot anymore
vector<Territory *> AggressivePlayer::toAttack(){
    vector<Territory *> territoriesToAttack; //Create empty vector
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
    Order *order;
    int reinforcementPool = p->getReinforcementPool();
    OrdersList *orderList = p->getOrderList();
    Map *map = p->getPlayerMap();

    if(type=="Deploy"){
        vector<Territory *> toAttackList = toAttack();//Empty for benevolent player
        vector<Territory *> toDefendList = toDefend();
        if (reinforcementPool > 0) {
            while (reinforcementPool > 0) {
                //Benevolent player deploys armies on its weakest country
                Territory* weakestTerritory = toDefendList.front();
                int deployAmount = reinforcementPool;
                order = new DeployOrder(weakestTerritory, deployAmount, p->getName());
                reinforcementPool -= deployAmount;
                orderList->addOrder(order);
            }
        }
        else {
            cout << "User has no reinforcements!" << endl;
        }
    }

    if(type=="Advance"){
        vector<Territory *> toDefendList = toDefend();

        //Benevolent player advances armies from the strongest adjacent territory to the weakest
        Territory *targetTerritory = toDefendList.front() ;
        //Find the strongest territory adjacent to the targetTerritory
        Territory *strongestAdjacentTerritory = nullptr;
        int maxArmies = 0;

        for (Territory *adjTerritory : map->getNeighborsPointers(targetTerritory->getName())) {
            if (adjTerritory->getPlayer() == p->getName() && adjTerritory->getArmies() > maxArmies) {
                maxArmies = adjTerritory->getArmies();
                strongestAdjacentTerritory = adjTerritory;
            }
        }

        //If a strongest adjacent territory is found, advance armies from it
        if (strongestAdjacentTerritory != nullptr) {
            if(strongestAdjacentTerritory->getArmies()>0){
                int armiesToAdvance = strongestAdjacentTerritory->getArmies() / 2;
                order = new AdvanceOrder(strongestAdjacentTerritory, targetTerritory, armiesToAdvance, map, p->getName());
                orderList->addOrder(order);
            }
            else{
                cout<<"Source Territory has no armies"<<endl;
            }
        }
        
    }
    else if(type=="Bomb"){
        //Benevolent player never bombs territories
        cout << "Benevolent player does not bomb territories." << endl;
    }
    else if(type=="Airlift"){//Armies are already checked in the execute() method, so no need to check armies here
        vector<Territory *> toDefendList = toDefend();

        //Randomly select a source territory for the AirliftOrder
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> sourceDistribution(0, p->getPlayerTerritories().size() - 1);
        Territory *sourceTerritory = p->getPlayerTerritories().at(sourceDistribution(gen));

        // Move armies from source to the front of toDefendList using AirliftOrder
        int airliftArmies = sourceTerritory->getArmies() / 2; //Move half of the armies
        Territory *targetTerritory = toDefend().front();
        order = new AirliftOrder(sourceTerritory, targetTerritory, airliftArmies, p->getName());
        orderList->addOrder(order);
    }
    else if(type=="Blockade"){
        //Get the weakest territory owned by the player
        vector<Territory*> toDefendList = toDefend();
        if (!toDefendList.empty()) {
            Territory* targetTerritory = toDefendList.front();

            //Create and add the BlockadeOrder to the order list
            order = new BlockadeOrder(targetTerritory, p->getName());
            orderList->addOrder(order);
        } 
        else {
            cout << "Blockade order is invalid. No territories to defend." << endl;
        }
    }
    else if(type=="Negotiate"){
        //Randomly select a target player for the NegotiateOrder
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> playerDistribution(0, p->getAllPlayers().size() - 1);
        string targetPlayer = p->getAllPlayers().at(playerDistribution(gen))->getName();

        //Create and add the NegotiateOrder to the order list
        order = new NegotiateOrder(p->getName(), targetPlayer);
        orderList->addOrder(order);
    }
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

