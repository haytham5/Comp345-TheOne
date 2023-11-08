#include "Order.h"
#include <iostream>
#define NEUTRAL "Unassigned"

Order &Order::operator=(const Order &other)
 {
    description = other.description;
    isExecuted = other.isExecuted;
    return *this;
}
std::string Order::getDescription() const
{
    return description;
}

bool Order::hasExecuted() const { 
    return isExecuted; 
}

OrdersList::OrdersList() {}

// Copy constructor
OrdersList::OrdersList(const OrdersList& other) {
    for (Order* order : other.orders) {
        // Deep copy: create a new order and copy its content.
        this->orders.push_back(new DeployOrder(*dynamic_cast<DeployOrder*>(order)));
    }
}

// Destructor
OrdersList::~OrdersList() {
    cout << "Deleting Orderlist..."<<endl;
    for (Order* order : orders) {
        delete order;
    }
    orders.clear();
}

// Methods
void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
}

void OrdersList::removeOrder(Order* order) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (*it == order) {
            delete *it;  // Free the memory of the order object
            orders.erase(it);  // Remove the pointer from the list
            return;
        }
    }
}

void OrdersList::moveOrder(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= orders.size() || toIndex < 0 || toIndex >= orders.size()) {
        throw std::out_of_range("Index out of range.");
    }
    std::iter_swap(orders.begin() + fromIndex, orders.begin() + toIndex);
}

OrdersList &OrdersList::operator=(const OrdersList &other)
{
    orders = other.orders;
    return *this;
}

const std::vector<Order*>& OrdersList::getOrders() const {
    return orders;
}

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    for (const Order* order : ordersList.orders) {
        os << order->getDescription() << "\n";
    }
    return os;
}

ostream &operator<<(ostream &out, const DeployOrder &object)
{
    out << object.description << "; Executed: " << 
    object.isExecuted << "; Target Territory: " << 
    object.targetTerritory << "; Number of Armies: " <<
    object.numberOfArmies << endl;
    return out;
}

ostream &operator<<(ostream &out, const AdvanceOrder &object)
{
    out << object.description << "; Executed: " << 
    object.isExecuted << "; Target Territory: " << 
    object.targetTerritory << "; Source Territory : " << 
    object.sourceTerritory << "; Number of Armies: " <<
    object.numberOfArmies << endl;
    return out;
}

ostream &operator<<(ostream &out, const AirliftOrder &object)
{
    out << object.description << "; Executed: " << 
    object.isExecuted << "; Target Territory: " << 
    object.targetTerritory << "; Source Territory : " << 
    object.sourceTerritory << "; Number of Armies: " <<
    object.numberOfArmies << endl;
    return out;
}

ostream &operator<<(ostream &out, const BlockadeOrder &object)
{
    out << object.description << "; Executed: " << 
    object.isExecuted << "; Target Territory: " << 
    object.targetTerritory << "; Source Territory : " << endl;
    return out;
}
ostream &operator<<(ostream &out, const BombOrder &object)
{
    out << object.description << "; Executed: " << 
    object.isExecuted << "; Target Territory: " << 
    object.targetTerritory << "; Source Territory : " << endl;
    return out;
}
AdvanceOrder::AdvanceOrder()
{
    description = "Advance";
}

AdvanceOrder::AdvanceOrder(Territory *source, Territory *target, int armies, Map* gameMap, const std::string& player)
    : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies), gameMap(gameMap), issuingPlayer(player)
{
    description = "Advance " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName() + " by player " + issuingPlayer;
}

AdvanceOrder &AdvanceOrder::operator=(const AdvanceOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    sourceTerritory = other.sourceTerritory;
    numberOfArmies = other.numberOfArmies;
    return *this;
}

bool AdvanceOrder::validate() {
    // Check if the source territory belongs to the player issuing the order
    if (sourceTerritory->getPlayer() != issuingPlayer) {
        return false;
    }

    // Check if the target territory is adjacent to the source territory
    vector<string> neighbors = gameMap->getNeighbors(sourceTerritory->getName());
    if (find(neighbors.begin(), neighbors.end(), targetTerritory->getName()) == neighbors.end()) {
        return false; // Target territory is not in the list of neighbors
    }

    return true;
}

void AdvanceOrder::execute() {
    if (validate()) {
        if (targetTerritory->getPlayer() != issuingPlayer) {
            // Simulate a battle
            //simulateBattle();
            cout << "Simulating battle" << endl;
        } else {
            // Move armies without a battle
            sourceTerritory->setArmies(sourceTerritory->getArmies() - numberOfArmies);
            targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        }

        isExecuted = true;
    } else {
        std::cout << "Advance order is invalid and cannot be executed." << std::endl;
    }
}

AirliftOrder::AirliftOrder()
{
    description = "Airlift";
}

AirliftOrder::AirliftOrder(Territory *source, Territory *target, int armies, const std::string& player)
    : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies), issuingPlayer(player)
{
    description = "Airlift " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName() + " by " + issuingPlayer;
}

AirliftOrder &AirliftOrder::operator=(const AirliftOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    sourceTerritory = other.sourceTerritory;
    numberOfArmies = other.numberOfArmies;
    return *this;
}

bool AirliftOrder::validate() {
    if (sourceTerritory == nullptr || targetTerritory == nullptr) {
        return false; // Check for null pointers
    }

    // Check if both territories belong to the player issuing the order
    return sourceTerritory->getPlayer() == issuingPlayer && targetTerritory->getPlayer() == issuingPlayer;
}

void AirliftOrder::execute() {
    if (validate()) {
        if (validate()) {
        int currentSourceArmies = sourceTerritory->getArmies();
        int currentTargetArmies = targetTerritory->getArmies();

        // Check if the source territory has enough armies
        if (numberOfArmies <= currentSourceArmies) {
            sourceTerritory->setArmies(currentSourceArmies - numberOfArmies);
            targetTerritory->setArmies(currentTargetArmies + numberOfArmies);
            isExecuted = true;
        } else {
            std::cout << "Not enough armies in the source territory to execute airlift." << std::endl;
        }
    } else {
        std::cout << "Airlift order is invalid and cannot be executed." << std::endl;
    }
    }
}

BlockadeOrder::BlockadeOrder()
{
    description = "Blockade";
}

BlockadeOrder::BlockadeOrder(Territory *target)
    : targetTerritory(target)
{
    description = "Blockade " + target->getName();
}

BlockadeOrder &BlockadeOrder::operator=(const BlockadeOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    return *this;
}

bool BlockadeOrder::validate() {
    // Logic to validate the blockade order.
    //TODO: return targetTerritory->getPlayer() == NEUTRAL;
    return true;
}

void BlockadeOrder::execute() {
    if (validate()) {
        // targetTerritory->setArmies(targetTerritory->getArmies() * 3);
        // //TODO: Figure out what being neutral means type shit 
        // isExecuted = true;

        cout << "Blockading" << endl;
    }
}

DeployOrder::DeployOrder()
{
    description = "Deploy";
}

//added Player to the constructor
DeployOrder::DeployOrder(Territory *target, int armies, const std::string& player)
   
{
    description = "Deploy " + std::to_string(armies) + " to " + target->getName() + "by player " + issuingPlayer;
}

DeployOrder &DeployOrder::operator=(const DeployOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    numberOfArmies = other.numberOfArmies;
    return *this;
}

bool DeployOrder::validate() {
    if (targetTerritory == nullptr) {
        return false;
    }
    return targetTerritory->getPlayer() == issuingPlayer;
}

void DeployOrder::execute() {
    if (validate()) {
        // Add the specified number of armies to the target territory
        int currentArmies = targetTerritory->getArmies();
        targetTerritory->setArmies(currentArmies + numberOfArmies);

        // Set the order as executed
        isExecuted = true;

        std::cout << "Deployed " << numberOfArmies << " armies to " << targetTerritory->getName() << std::endl;
    } else {
        std::cout << "Deploy order is invalid and cannot be executed." << std::endl;
    }
}

BombOrder::BombOrder()
{
    description = "bomb";
}

BombOrder::BombOrder(Territory *target, const std::string& player, Map* gameMap)
 : targetTerritory(target), issuingPlayer(player), gameMap(gameMap) {
    description = "Bomb " + target->getName() + " by " + issuingPlayer;
}

BombOrder &BombOrder::operator=(const BombOrder &other)
{
    if (this != &other) {
        description = other.description;
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        issuingPlayer = other.issuingPlayer;
        gameMap = other.gameMap;
    }
    return *this;
}

bool BombOrder::validate()  {
  if (targetTerritory == nullptr) {
        return false; // Check for null pointer
    }

    // Check if the target territory belongs to another player
    if (targetTerritory->getPlayer() == issuingPlayer) {
        return false;
    }

     // Check if the target territory is adjacent to any territory owned by the issuing player
    for (Territory* ownedTerritory : gameMap->getTerritories()) {
        if (ownedTerritory != nullptr && ownedTerritory->getPlayer() == issuingPlayer) {
            vector<string> neighbors = gameMap->getNeighbors(ownedTerritory->getName());
            if (find(neighbors.begin(), neighbors.end(), targetTerritory->getName()) != neighbors.end()) {
                return true; // Found an adjacent territory owned by the player
            }
        }
    }

    return false;
}

void BombOrder::execute()  {
     if (validate()) {
        int currentArmies = targetTerritory->getArmies();
        targetTerritory->setArmies(currentArmies / 2);  // Halve the armies
        isExecuted = true;
        std::cout << "Successfully bombed " << targetTerritory->getName() << ". Armies reduced to " << targetTerritory->getArmies() << std::endl;
    } else {
        std::cout << "Bomb order is invalid and cannot be executed." << std::endl;
    }
}

void testOrdersList() {
    std::cout << "===== Testing Orders Lists =====" << std::endl;

    // Creating territories and players for testing
    Territory territory1("Territory1", 0, 0, "ContinentA");
    Territory territory2("Territory2", 1, 1, "ContinentA");
    // Player player1("Player1");
    // Player player2("Player2");
    // Creating a map and adding territories (and possibly setting adjacency)
    Map gameMap;
    gameMap.addTerritory("Territory1", 0, 0, "ContinentA");
    gameMap.addTerritory("Territory2", 1, 1, "ContinentA");
    // Creating orders
    DeployOrder* deployOrder = new DeployOrder(&territory1, 5, "Player1");
    AdvanceOrder* advanceOrder = new AdvanceOrder(&territory1, &territory2, 3, &gameMap, "Player1");
    BombOrder* bombOrder = new BombOrder(&territory2, "Player1", &gameMap);
    BlockadeOrder* blockadeOrder = new BlockadeOrder(&territory1);
    AirliftOrder* airliftOrder = new AirliftOrder(&territory1, &territory2, 2, "Player1");
    //NegotiateOrder* negotiateOrder = new NegotiateOrder(&player2);

    // Add orders to an OrdersList
    OrdersList orders;
    orders.addOrder(deployOrder);
    orders.addOrder(advanceOrder);
    orders.addOrder(bombOrder);
    orders.addOrder(blockadeOrder);
    orders.addOrder(airliftOrder);
    //orders.addOrder(negotiateOrder);

    // Display orders before execution
    std::cout << "\nOrders List before execution:" << std::endl;
    std::cout << orders << endl;

    std::cout << "\nExecuting All orders after validation:" << endl;

    // Validate and execute orders
    for (Order* order : orders.getOrders()) {
        if (order->validate()) {
            order->execute();
            std::cout << order->getDescription() << " executed successfully!" << std::endl;
        } else {
            std::cout << order->getDescription() << " validation failed!" << std::endl;
        }
    }


    // Show territory stats after order execution
    // std::cout << "\nTerritory stats after executing orders:" << std::endl;
    //std::cout << territory1.getName() << " has " << territory1.getArmies() << " armies. Neutral: " << (territory1.isNeutral() ? "Yes" : "No") << std::endl;
    // std::cout << territory2.getName() << " has " << territory2.getArmies() << " armies." << std::endl;

    // Move orders for demonstration
    std::cout << "\nMoving orders..." << std::endl;
    orders.moveOrder(0, 1);
    
    cout <<"\nOrders after movement (first Order placed second): " << endl;
    std::cout << orders;

    // Remove orders for demonstration
    std::cout << "\nRemoving orders..." << std::endl;
    orders.removeOrder(deployOrder);

    cout <<"\nOrders after removal (removing second order): " << endl;
    std::cout << orders;

    std::cout << "===== Testing Complete =====" << std::endl;
}

ostream &operator<<(ostream &out, const Order &object)
{
    out << object.description << "; Executed: " << object.isExecuted << endl;
    return out;
}