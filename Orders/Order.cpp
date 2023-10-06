#include "Order.h"
#include <iostream>
#define NEUTRAL "Unassigned"

std::string Order::getDescription() const { 
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

const std::vector<Order*>& OrdersList::getOrders() const {
    return orders;
}

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    for (const Order* order : ordersList.orders) {
        os << order->getDescription() << "\n";
    }
    return os;
}

AdvanceOrder::AdvanceOrder()
{
    description = "Advance";
}

AdvanceOrder::AdvanceOrder(Territory *source, Territory *target, int armies)
    : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies)
{
    description = "Advance " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName();
}

bool AdvanceOrder::validate() {
    // Logic to validate the advance order.
    // For example, the source territory must have enough armies to advance.
    return sourceTerritory->getArmies() >= numberOfArmies;
}

void AdvanceOrder::execute() {
    if (validate()) {
        // sourceTerritory->setArmies(sourceTerritory->getArmies() - numberOfArmies);
        // targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        // isExecuted = true;

        cout << "Advance" << endl;
    }
}

AirliftOrder::AirliftOrder()
{
    description = "Airlift";
}

AirliftOrder::AirliftOrder(Territory *source, Territory *target, int armies)
    : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies)
{
    description = "Airlift " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName();
}

bool AirliftOrder::validate() {
    // Logic to validate the airlift order.
    return sourceTerritory->getArmies() >= numberOfArmies;
}

void AirliftOrder::execute() {
    if (validate()) {
        // sourceTerritory->setArmies(sourceTerritory->getArmies() - numberOfArmies);
        // targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        // isExecuted = true;

        cout << "Airlift" << endl;
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

bool BlockadeOrder::validate() {
    // Logic to validate the blockade order.
    return targetTerritory->getPlayer() == NEUTRAL;
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

DeployOrder::DeployOrder(Territory *target, int armies)
    : targetTerritory(target), numberOfArmies(armies)
{
    description = "Deploy " + std::to_string(armies) + " to " + target->getName();
}

bool DeployOrder::validate() {
    // Here you would implement the validation logic for a Deploy order.
    // This is just a mock implementation.
    return targetTerritory != nullptr && numberOfArmies > 0;
}

void DeployOrder::execute() {
    // Here you would implement the action for the Deploy order.
    // For example, increasing the number of armies in the target territory.
    // This is a mock implementation for demonstration purposes.
    if (validate()) {
        // targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        // isExecuted = true;
        cout << "Deploy" << endl; 
    }
}

BombOrder::BombOrder()
{
    description = "bomb";
}

BombOrder::BombOrder(Territory *target)
{
    description = "Bomb " + target->getName();
}

bool BombOrder::validate()  {
// Simple validation: Target territory must have armies.
    return targetTerritory->getArmies() > 0;
}

void BombOrder::execute()  {
    if (validate()) {
        // targetTerritory->setArmies(targetTerritory->getArmies() / 2);  // Reduce armies by half as an example effect of bombing.
        // isExecuted = true;
        cout << "Bomb" << endl;
    }
}
