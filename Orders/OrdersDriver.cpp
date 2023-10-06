#include "Order.h"
#include "..\Map\Map.h"
#include <iostream>

using namespace std;

void testOrdersLists() {
    std::cout << "===== Testing Orders Lists =====" << std::endl;

    // Creating territories and players for testing
    Territory territory1("Territory1", 0, 0, "ContinentA");
    Territory territory2("Territory2", 1, 1, "ContinentA");
    // Player player1("Player1");
    // Player player2("Player2");

    // Creating orders
    DeployOrder* deployOrder = new DeployOrder(&territory1, 5);
    AdvanceOrder* advanceOrder = new AdvanceOrder(&territory1, &territory2, 3);
    BombOrder* bombOrder = new BombOrder(&territory2);
    BlockadeOrder* blockadeOrder = new BlockadeOrder(&territory1);
    AirliftOrder* airliftOrder = new AirliftOrder(&territory1, &territory2, 2);
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
    std::cout << orders;

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
    std::cout << "\nTerritory stats after executing orders:" << std::endl;
    //std::cout << territory1.getName() << " has " << territory1.getArmies() << " armies. Neutral: " << (territory1.isNeutral() ? "Yes" : "No") << std::endl;
    std::cout << territory2.getName() << " has " << territory2.getArmies() << " armies." << std::endl;

    // Move orders for demonstration
    std::cout << "\nMoving orders..." << std::endl;
    orders.moveOrder(0, 1);
    std::cout << orders;

    // Remove orders for demonstration
    std::cout << "\nRemoving orders..." << std::endl;
    orders.removeOrder(deployOrder);
    std::cout << orders;

    std::cout << "===== Testing Complete =====" << std::endl;
}

int main() {
    testOrdersLists();
    return 0;
}
