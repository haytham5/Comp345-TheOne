#include "PlayerStrategies.h"
#include "../Player/Player.h"
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

string PlayerStrategy::getType()
{
    return type;
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
HumanPlayer::HumanPlayer(Player *player) : PlayerStrategy(player){type = "human";}

HumanPlayer::HumanPlayer(const HumanPlayer &other) : PlayerStrategy(other){type = "human";}

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
                std::cout << "Player: " << p->getName() << " has " << reinforcementPool << " army units available to deploy and has " << toDefendList.size() << " territories \n";

                for (int i = 0; i < toDefendList.size(); i++)
                {
                    int deployAmount;
                    std::cout << "How many units would you like to deploy to territory: " << toDefendList[i]->getName() << "? ";
                    std::cin >> deployAmount;
                    order = new DeployOrder(toDefendList.at(i), deployAmount, p->getName());
                    reinforcementPool -= deployAmount;
                    std::cout << "Reinforcements after deployment: " << reinforcementPool;
                    orderList->addOrder(order);
                }
            }
        }
        else {
            std::cout << "User has no reinforcements!" << endl;
        }
    }
    else if (type == "Advance")
    {
        string attackOrDefend;
        std::cout << "Player: " << p->getName() << " would you like to move units to defend or attack teritories? Enter Defend or Attack: ";
        std::cin >> attackOrDefend;
        while (attackOrDefend != "")
        {
            if (attackOrDefend == "Defend")
            {
                std::cout << "Player : " << p->getName() << " your territories are: ";
                for (int i = 0; i < toDefendList.size(); i++)
                {
                    std::cout << toDefendList[i]->getName() << ": " << toDefendList[i]->getArmies() << " army units\n";
                }
                string territory1;
                int territory1Size;
                string territory2;
                int numToMove;
                std::cout << "Which territory would you like to move army units from?";
                std::cin >> territory1;
                for (int i = 0; i < toDefendList.size(); i++)
                {
                    if (territory1 == toDefendList[i]->getName())
                    {
                        territory1Size = toDefendList.size();
                    }
                }
                std::cout << "Territory: " << territory1 << " currently has " << territory1Size << " army units\n";
                std::cout << "How many army units would you like to move?";
                std::cin >> numToMove;
                std::cout << "To which territory would you like to send them to?";
                std::cin >> territory2;
                for (int i = 0; i < toDefendList.size(); i++)
                {
                    if (territory2 == toDefendList[i]->getName())
                    {
                        int armies = numToMove + toDefendList[i]->getArmies();
                        order = new DeployOrder(toDefendList[i], armies, "Player1");
                        std::cout << "Territory: " << territory2 << " now has " << toDefendList[i]->getArmies() << " army units\n";
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
                std::cout << "Player : " << p->getName() << " your territories are: ";
                for (int i = 0; i < toDefendList.size(); i++)
                {
                    std::cout << toDefendList[i]->getName() << ": " << toDefendList[i]->getArmies() << " army units\n";
                }
                string territory1;
                int numToMove;
                string territory2;
                std::cout << "From which territory would you like to move your army units from?";
                std::cin >> territory1;
                Territory *sourceTeritory;
                for (int i = 0; i < toDefendList.size(); i++)
                {
                    if (territory1 == toDefendList[i]->getName())
                    {
                        sourceTeritory = toDefendList[i];
                    }
                }
                std::cout << "How many army units from territory " << territory1 << " would you like to move?";
                std::cin >> numToMove;
                std::cout << "Which of the following neighboring territories would you like to attack? \n";
                for (int i = 0; i < toAttackList.size(); i++)
                {
                    std::cout << toAttackList[i]->getName() << "\n";
                }
                std::cin >> territory2;
                for (int i = 0; i < toAttackList.size(); i++)
                {
                    if (territory2 == toAttackList[i]->getName())
                    {
                        const string& c = "Player1";
                        if(sourceTeritory->getArmies()>0){
                            order = new AdvanceOrder(sourceTeritory, toAttackList[i], numToMove, map, c);
                            std::cout << numToMove << " army units have been advanced to territory " << territory2 << "\n";
                        }
                        else{
                            std::cout<<"Source territory has no armies"<<endl;
                        }
                    }
                }
            }
            else
            {
                std::cout << "Invalid command. Try again";
                std::cin >> attackOrDefend;
            }
        }
    }
    else if (type == "Bomb")
    {
        std::cout << "Player " << p->getName() << ", you have chosen to play the Bomb order." << endl;
        std::cout << "Select a territory to bomb:" << endl;

        //Display the territories that can be targeted
        vector<Territory*> targetableTerritories = p->toAttack();
        std::cout << "Available territories to bomb:" << endl;
        for (int i = 0; i < targetableTerritories.size(); ++i) {
            std::cout << i + 1 << ". " << targetableTerritories[i]->getName() << endl;
        }

        //Get user input for the territory to bomb
        int choice;
        std::cout << "Enter the number of the territory to bomb: ";
        std::cin >> choice;

        // Check if the choice is valid
        if (choice >= 1 && choice <= targetableTerritories.size()) {
            //Create and add the Bomb order to the player's order list
            Order* order = new BombOrder(targetableTerritories[choice - 1],p->getName(),map);
            p->getOrderList()->addOrder(order);
        } else {
            std::cout << "Invalid choice. Bomb order not issued." << endl;
        }
    }
    else if (type == "Airlift")
    {
        std::cout << "Player " << p->getName() << ", you have chosen to play the Airlift order." << endl;

        //Display the territories that can be used as source
        vector<Territory*> sourceTerritories = p->toDefend();

        std::cout << "Available source territories for airlift:" << endl;
        for (int i = 0; i < sourceTerritories.size(); ++i) {
            std::cout << i + 1 << ". " << sourceTerritories[i]->getName() << endl;
        }

        //Get user input for the source territory
        int sourceChoice;
        std::cout << "Enter the number of the source territory: ";
        std::cin >> sourceChoice;

        // Check if the source choice is valid
        if (sourceChoice >= 1 && sourceChoice <= sourceTerritories.size()) {
            // Display all territories (own and enemy) as potential targets
            vector<Territory*> allTargetTerritories = p->toDefend();
            vector<Territory*> enemyTargetTerritories = p->toAttack();

            allTargetTerritories.insert(allTargetTerritories.end(), enemyTargetTerritories.begin(), enemyTargetTerritories.end());

            std::cout << "Available target territories for airlift:" << endl;
            for (int i = 0; i < allTargetTerritories.size(); ++i) {
                std::cout << i + 1 << ". " << allTargetTerritories[i]->getName() << endl;
            }

            //Get user input for the target territory
            int targetChoice;
            std::cout << "Enter the number of the target territory: ";
            std::cin >> targetChoice;

            //Check if the target choice is valid
            if (targetChoice >= 1 && targetChoice <= allTargetTerritories.size()) {
                //Get user input for the number of armies to airlift
                int numArmies;
                std::cout << "Enter the number of armies to airlift: ";
                std::cin >> numArmies;

                //Create and add the Airlift order to the player's order list
                Order* order = new AirliftOrder(sourceTerritories[sourceChoice - 1], allTargetTerritories[targetChoice - 1], numArmies, p->getName());
                p->getOrderList()->addOrder(order);
            } else {
                std::cout << "Invalid target choice. Airlift order not issued." << endl;
            }
        } else {
            std::cout << "Invalid source choice. Airlift order not issued." << endl;
        }
    }
    else if (type == "Blockade")
    {
        std::cout << "Player " << p->getName() << ", you have chosen to play the Blockade order." << endl;

        // Display the territories that can be blockaded
        vector<Territory*> territoriesToBlockade = p->toDefend();

        std::cout << "Available territories to blockade:" << endl;
        for (int i = 0; i < territoriesToBlockade.size(); ++i) {
            std::cout << i + 1 << ". " << territoriesToBlockade[i]->getName() << endl;
        }

        // Get user input for the territory to blockade
        int blockadeChoice;
        std::cout << "Enter the number of the territory to blockade: ";
        std::cin >> blockadeChoice;

        // Check if the blockade choice is valid
        if (blockadeChoice >= 1 && blockadeChoice <= territoriesToBlockade.size()) {
            //Create and add the Blockade order to the player's order list
            Order* order = new BlockadeOrder(territoriesToBlockade[blockadeChoice - 1],p->getName());
            p->getOrderList()->addOrder(order);
        } else {
            std::cout << "Invalid blockade choice. Blockade order not issued." << endl;
        }
    }
    else if(type=="Negotiate"){
        std::cout << "Player " << p->getName() << ", you have chosen to play the Negotiate order." << endl;

        //Display the other players in the game
        vector<Player*> allPlayers = p->getAllPlayers();

        std::cout << "Other players in the game:" << endl;
        for (int i = 0; i < allPlayers.size(); ++i) {
            if (allPlayers[i] != p) {
                std::cout << i + 1 << ". " << allPlayers[i]->getName() << endl;
            }
        }

        //Get user input for the player to negotiate with
        int negotiateChoice;
        std::cout << "Enter the number of the player to negotiate with: ";
        std::cin >> negotiateChoice;

        //Check if the negotiate choice is valid
        if (negotiateChoice >= 1 && negotiateChoice <= allPlayers.size() - 1) {
            Player* otherPlayer = allPlayers[negotiateChoice - 1];

            //Create and add the Negotiate order to the player's order list
            Order* order = new NegotiateOrder(p->getName(),otherPlayer->getName());//Issuing player is first param, targetPlayer is second param
            p->getOrderList()->addOrder(order);
        } else {
            std::cout << "Invalid negotiate choice. Negotiate order not issued." << endl;
        }
    }
    else{
        std::cout<<"Invalid type in issueOrder(type), no order instance was created."<<endl;
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
AggressivePlayer::AggressivePlayer(Player *player) : PlayerStrategy(player){type = "aggressive";}

AggressivePlayer::AggressivePlayer(const AggressivePlayer& other) : PlayerStrategy(other) {type = "aggressive";}

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
            } cout << "HERE" << endl;
        }
        else {
        std::cout << "User has no reinforcements!" << endl;
        }
    }
    else if(type=="Advance"){
        vector<Territory *> toAttackList = toAttack();
        vector<Territory *> toDefendList = toDefend();
        for (Territory *sourceTerritory : p->getPlayerTerritories()) {
            for (Territory *targetTerritory : toAttackList) {
                cout << "Possible Target: " << *targetTerritory << endl;
                if(sourceTerritory->getArmies()>0){
                    order = new AdvanceOrder(sourceTerritory, targetTerritory, sourceTerritory->getArmies(), map, p->getName());
                    orderList->addOrder(order);
                    sourceTerritory->setArmies(0);
                }
                else{
                    std::cout<<"Source territory has no armies"<<endl;
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
            std::cout << "No enemy territories to bomb." << endl;
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
            std::cout << "Blockade order is invalid. No territories to defend." << endl;
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
BenevolentPlayer::BenevolentPlayer(Player *player) : PlayerStrategy(player){type = "benevolent";}

BenevolentPlayer::BenevolentPlayer(const BenevolentPlayer& other) : PlayerStrategy(other) {type = "benevolent";}

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
            std::cout << "User has no reinforcements!" << endl;
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
                std::cout<<"Source Territory has no armies"<<endl;
            }
        }
        
    }
    else if(type=="Bomb"){
        //Benevolent player never bombs territories
        std::cout << "Benevolent player does not bomb territories." << endl;
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
            std::cout << "Blockade order is invalid. No territories to defend." << endl;
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
NeutralPlayer::NeutralPlayer(Player *player) : PlayerStrategy(player){type = "neutral";}

NeutralPlayer::NeutralPlayer(const NeutralPlayer& other) : PlayerStrategy(other) {type = "neutral";}

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

// NeutralPlayer Implementation
void NeutralPlayer::issueOrder(string type) {
   if (p->getWasAttacked()) {
    // Change the strategy to Aggressive
    p->setPlayerStrategy(new AggressivePlayer(p));
    std::cout << p->getName() << " is now Aggressive after being attacked." << std::endl;

    p->issueOrder(type);

    p->setWasAttacked(false);  // Reset the attacked status
    } else {
    std::cout << "Neutral player does not issue any orders." << std::endl;
    }
}

vector<Territory*> NeutralPlayer::toDefend(){
    return vector<Territory*>(); // Returns an empty vector as Neutral player doesn't defend.
}

vector<Territory*> NeutralPlayer::toAttack(){
    return vector<Territory*>(); // Returns an empty vector as Neutral player doesn't attack.
}

//CHEATER PLAYER
CheaterPlayer::CheaterPlayer(Player *player) : PlayerStrategy(player){type = "cheater";}

CheaterPlayer::CheaterPlayer(const CheaterPlayer& other) : PlayerStrategy(other) {type = "cheater";}

CheaterPlayer::~CheaterPlayer(){

}



// CheaterPlayer Implementation
void CheaterPlayer::issueOrder(string type){
    if (type == "Conquer") {
        auto playerTerritories = p->getPlayerTerritories();
        Map* map = p->getPlayerMap();
        for (auto& territory : playerTerritories) {
            vector<string> neighbors = map->getNeighbors(territory->getName());
            for (auto& neighborName : neighbors) {
                Territory* neighbor = map->getTerritory(neighborName);
                if (neighbor->getPlayer() != p->getName()) {
                    // Automatically conquer neighbor territory
                    neighbor->setPlayer(p->getName());
                    std::cout << "Cheater player has conquered " << neighborName << endl;
                }
            }
        }
    } else {
        std::cout << "Cheater player does not issue '" << type << "' orders." << endl;
    }
}

vector<Territory*> CheaterPlayer::toDefend(){
    return p->getPlayerTerritories(); // Returns all owned territories.
}

vector<Territory*> CheaterPlayer::toAttack(){
    vector<Territory*> attackableTerritories;
    auto playerTerritories = p->getPlayerTerritories();
    Map* map = p->getPlayerMap();
    for (auto& territory : playerTerritories) {
        vector<string> neighbors = map->getNeighbors(territory->getName());
        for (auto& neighborName : neighbors) {
            Territory* neighbor = map->getTerritory(neighborName);
            if (neighbor->getPlayer() != p->getName()) {
                attackableTerritories.push_back(neighbor);
            }
        }
    }
    return attackableTerritories; // Returns neighboring enemy territories.
}

//Free function
void testPlayerStrategies() {
    std::cout << "===== Testing Player Strategies =====" << std::endl;

    // Create a map and players for testing
    Map gameMap; 
    // Initialize territories for the map 
    gameMap.addTerritory("Territory1", 0, 0, "ContinentA");
    gameMap.addTerritory("Territory2", 0, 1, "ContinentA");
    gameMap.addTerritory("Territory3", 1, 0, "ContinentA");
    gameMap.addTerritory("Territory4", 1, 1, "ContinentA");
    gameMap.addTerritory("Territory5", 1, 2, "ContinentA");

    gameMap.addEdge("Territory1", "Territory2");
    gameMap.addEdge("Territory1", "Territory3");
    gameMap.addEdge("Territory2", "Territory4");
    gameMap.addEdge("Territory3", "Territory4");
    gameMap.addEdge("Territory5", "Territory4");

    Deck* sharedDeck = new Deck();

    // Create players with different strategies
    Player humanPlayer("Human", &gameMap, new Hand(sharedDeck), new OrdersList());
    Player aggressivePlayer("Aggressive", &gameMap, new Hand(sharedDeck), new OrdersList());
    Player benevolentPlayer("Benevolent", &gameMap, new Hand(sharedDeck), new OrdersList());
    Player neutralPlayer("Neutral", &gameMap, new Hand(sharedDeck), new OrdersList());
    Player cheaterPlayer("Cheater", &gameMap, new Hand(sharedDeck), new OrdersList());

    //Assign Territories to Players
    humanPlayer.addPlayerTerritories(gameMap.getTerritory("Territory1"));
    aggressivePlayer.addPlayerTerritories(gameMap.getTerritory("Territory2"));
    benevolentPlayer.addPlayerTerritories(gameMap.getTerritory("Territory3"));
    neutralPlayer.addPlayerTerritories(gameMap.getTerritory("Territory4"));
    cheaterPlayer.addPlayerTerritories(gameMap.getTerritory("Territory5"));


    // Assign strategies to players
    humanPlayer.setPlayerStrategy(new HumanPlayer(&humanPlayer));
    aggressivePlayer.setPlayerStrategy(new AggressivePlayer(&aggressivePlayer));
    benevolentPlayer.setPlayerStrategy(new BenevolentPlayer(&benevolentPlayer));
    neutralPlayer.setPlayerStrategy(new NeutralPlayer(&neutralPlayer));
    cheaterPlayer.setPlayerStrategy(new CheaterPlayer(&cheaterPlayer));

    // Demonstrate behavior of each player strategy
    std::cout << "\nHuman Player issuing an order:" << std::endl;
    humanPlayer.issueOrder("Deploy");

    cout << "Issued Order for Human Player: ";
    humanPlayer.printOrderList();

    std::cout << "\nAggressive Player issuing an order:" << std::endl;
    aggressivePlayer.testTerritoryDeployment();

    aggressivePlayer.issueOrder("Advance");

    cout << "Issued Order for Aggressive Player: ";
    aggressivePlayer.printOrderList();

    std::cout << "\nBenevolent Player issuing an order:" << std::endl;
    benevolentPlayer.issueOrder("Deploy");

    cout << "Issued Order for Benevolent Player: ";
    benevolentPlayer.printOrderList();

    std::cout << "\nNeutral Player issuing an order." << std::endl;
    neutralPlayer.testTerritoryDeployment();
    neutralPlayer.issueOrder("Advance");

    cout << "Issued Order for Neutral Player: ";
    neutralPlayer.printOrderList();

    std::cout << "\nCheater Player issuing an order:" << std::endl;
    cheaterPlayer.issueOrder("Conquer");

    // Dynamically change strategy of a player
    std::cout << "\nChanging strategy of Neutral Player to Aggressive:" << std::endl;
    neutralPlayer.setPlayerStrategy(new AggressivePlayer(&neutralPlayer));
    neutralPlayer.issueOrder("Advance");

    std::cout << "===== Testing Complete =====" << std::endl;
}


