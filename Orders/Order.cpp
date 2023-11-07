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

bool Order::hasExecuted() const
{
    return isExecuted;
}

OrdersList::OrdersList() {}

// Copy constructor
OrdersList::OrdersList(const OrdersList &other)
{
    for (Order *order : other.orders)
    {
        // Deep copy: create a new order and copy its content.
        this->orders.push_back(new DeployOrder(*dynamic_cast<DeployOrder *>(order)));
    }
}

// Destructor
OrdersList::~OrdersList()
{
    cout << "Deleting Orderlist..." << endl;
    for (Order *order : orders)
    {
        delete order;
    }
    orders.clear();
}

// Methods
void OrdersList::addOrder(Order *order)
{
    orders.push_back(order);
}

int OrdersList::getOrdersListSize()
{
    return orders.size();
}

void OrdersList::removeOrder(Order *order)
{
    for (auto it = orders.begin(); it != orders.end(); ++it)
    {
        if (*it == order)
        {
            delete *it;       // Free the memory of the order object
            orders.erase(it); // Remove the pointer from the list
            return;
        }
    }
}

Order *OrdersList::getOrder(int index)
{
    if (index < orders.size() && index >= 0)
    {
        return orders[index];
    }
    return nullptr;
}

void OrdersList::moveOrder(int fromIndex, int toIndex)
{
    if (fromIndex < 0 || fromIndex >= orders.size() || toIndex < 0 || toIndex >= orders.size())
    {
        throw std::out_of_range("Index out of range.");
    }
    std::iter_swap(orders.begin() + fromIndex, orders.begin() + toIndex);
}

OrdersList &OrdersList::operator=(const OrdersList &other)
{
    orders = other.orders;
    return *this;
}

const std::vector<Order *> &OrdersList::getOrders() const
{
    return orders;
}

std::ostream &operator<<(std::ostream &os, const OrdersList &ordersList)
{
    for (const Order *order : ordersList.orders)
    {
        os << order->getDescription() << "\n";
    }
    return os;
}

ostream &operator<<(ostream &out, const DeployOrder &object)
{
    out << object.description << "; Executed: " << object.isExecuted << "; Target Territory: " << object.targetTerritory << "; Number of Armies: " << object.numberOfArmies << endl;
    return out;
}

ostream &operator<<(ostream &out, const AdvanceOrder &object)
{
    out << object.description << "; Executed: " << object.isExecuted << "; Target Territory: " << object.targetTerritory << "; Source Territory : " << object.sourceTerritory << "; Number of Armies: " << object.numberOfArmies << endl;
    return out;
}

ostream &operator<<(ostream &out, const AirliftOrder &object)
{
    out << object.description << "; Executed: " << object.isExecuted << "; Target Territory: " << object.targetTerritory << "; Source Territory : " << object.sourceTerritory << "; Number of Armies: " << object.numberOfArmies << endl;
    return out;
}

ostream &operator<<(ostream &out, const BlockadeOrder &object)
{
    out << object.description << "; Executed: " << object.isExecuted << "; Target Territory: " << object.targetTerritory << "; Source Territory : " << endl;
    return out;
}
ostream &operator<<(ostream &out, const BombOrder &object)
{
    out << object.description << "; Executed: " << object.isExecuted << "; Target Territory: " << object.targetTerritory << "; Source Territory : " << endl;
    return out;
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

AdvanceOrder &AdvanceOrder::operator=(const AdvanceOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    sourceTerritory = other.sourceTerritory;
    numberOfArmies = other.numberOfArmies;
    return *this;
}

bool AdvanceOrder::validate()
{
    // Logic to validate the advance order.
    // For example, the source territory must have enough armies to advance.
    // TODO: return sourceTerritory->getArmies() >= numberOfArmies;
    return true;
}

void AdvanceOrder::execute()
{
    if (validate())
    {
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

AirliftOrder &AirliftOrder::operator=(const AirliftOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    sourceTerritory = other.sourceTerritory;
    numberOfArmies = other.numberOfArmies;
    return *this;
}

bool AirliftOrder::validate()
{
    // Logic to validate the airlift order.
    // TODO: return sourceTerritory->getArmies() >= numberOfArmies;
    return true;
}

void AirliftOrder::execute()
{
    if (validate())
    {
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

BlockadeOrder &BlockadeOrder::operator=(const BlockadeOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    return *this;
}

bool BlockadeOrder::validate()
{
    // Logic to validate the blockade order.
    // TODO: return targetTerritory->getPlayer() == NEUTRAL;
    return true;
}

void BlockadeOrder::execute()
{
    if (validate())
    {
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

DeployOrder &DeployOrder::operator=(const DeployOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    numberOfArmies = other.numberOfArmies;
    return *this;
}

bool DeployOrder::validate()
{
    // Here you would implement the validation logic for a Deploy order.
    // This is just a mock implementation.
    // return targetTerritory != nullptr && numberOfArmies > 0;
    return true;
}

void DeployOrder::execute()
{
    // Here you would implement the action for the Deploy order.
    // For example, increasing the number of armies in the target territory.
    // This is a mock implementation for demonstration purposes.
    if (validate())
    {
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

BombOrder &BombOrder::operator=(const BombOrder &other)
{
    description = other.description;
    isExecuted = other.isExecuted;
    targetTerritory = other.targetTerritory;
    return *this;
}

bool BombOrder::validate()
{
    // Simple validation: Target territory must have armies.
    // TODO: return targetTerritory->getArmies() > 0;
    return true;
}

void BombOrder::execute()
{
    if (validate())
    {
        // targetTerritory->setArmies(targetTerritory->getArmies() / 2);  // Reduce armies by half as an example effect of bombing.
        // isExecuted = true;
        cout << "Bomb" << endl;
    }
}

void testOrdersList()
{
    std::cout << "===== Testing Orders Lists =====" << std::endl;

    // Creating territories and players for testing
    Territory territory1("Territory1", 0, 0, "ContinentA");
    Territory territory2("Territory2", 1, 1, "ContinentA");
    // Player player1("Player1");
    // Player player2("Player2");

    // Creating orders
    DeployOrder *deployOrder = new DeployOrder(&territory1, 5);
    AdvanceOrder *advanceOrder = new AdvanceOrder(&territory1, &territory2, 3);
    BombOrder *bombOrder = new BombOrder(&territory2);
    BlockadeOrder *blockadeOrder = new BlockadeOrder(&territory1);
    AirliftOrder *airliftOrder = new AirliftOrder(&territory1, &territory2, 2);
    // NegotiateOrder* negotiateOrder = new NegotiateOrder(&player2);

    // Add orders to an OrdersList
    OrdersList orders;
    orders.addOrder(deployOrder);
    orders.addOrder(advanceOrder);
    orders.addOrder(bombOrder);
    orders.addOrder(blockadeOrder);
    orders.addOrder(airliftOrder);
    // orders.addOrder(negotiateOrder);

    // Display orders before execution
    std::cout << "\nOrders List before execution:" << std::endl;
    std::cout << orders << endl;

    std::cout << "\nExecuting All orders after validation:" << endl;

    // Validate and execute orders
    for (Order *order : orders.getOrders())
    {
        if (order->validate())
        {
            order->execute();
            std::cout << order->getDescription() << " executed successfully!" << std::endl;
        }
        else
        {
            std::cout << order->getDescription() << " validation failed!" << std::endl;
        }
    }

    // Show territory stats after order execution
    // std::cout << "\nTerritory stats after executing orders:" << std::endl;
    // std::cout << territory1.getName() << " has " << territory1.getArmies() << " armies. Neutral: " << (territory1.isNeutral() ? "Yes" : "No") << std::endl;
    // std::cout << territory2.getName() << " has " << territory2.getArmies() << " armies." << std::endl;

    // Move orders for demonstration
    std::cout << "\nMoving orders..." << std::endl;
    orders.moveOrder(0, 1);

    cout << "\nOrders after movement (first Order placed second): " << endl;
    std::cout << orders;

    // Remove orders for demonstration
    std::cout << "\nRemoving orders..." << std::endl;
    orders.removeOrder(deployOrder);

    cout << "\nOrders after removal (removing second order): " << endl;
    std::cout << orders;

    std::cout << "===== Testing Complete =====" << std::endl;
}

ostream &operator<<(ostream &out, const Order &object)
{
    out << object.description << "; Executed: " << object.isExecuted << endl;
    return out;
}