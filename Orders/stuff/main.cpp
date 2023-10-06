#include <iostream>
#include "DeployOrder.h"
#include "OrdersList.h"

int main() {
    // Create a few territories
    Territory territory1("Territory1", 0, 0, "ContinentA");
    Territory territory2("Territory2", 1, 1, "ContinentA");

    // Print initial state of the territories
    std::cout << "Initial state:" << std::endl;
    std::cout << territory1.getName() << " has " << territory1.getArmies() << " armies." << std::endl;
    std::cout << territory2.getName() << " has " << territory2.getArmies() << " armies." << std::endl;

    // Create some deploy orders
   DeployOrder* deployOrder1 = new DeployOrder(&territory1, 5);
DeployOrder* deployOrder2 = new DeployOrder(&territory2, 3);   

    // Add orders to an OrdersList
OrdersList orders;
orders.addOrder(deployOrder1);
orders.addOrder(deployOrder2);

    // Execute orders
    for (Order* order : orders.getOrders()) {
        if (order->validate()) {
            order->execute();
        } else {
            std::cout << "Order (" << order->getDescription() << ") validation failed!" << std::endl;
        }
    }

    // Print the state of the territories after executing orders
    std::cout << "\nAfter executing orders:" << std::endl;
    std::cout << territory1.getName() << " has " << territory1.getArmies() << " armies." << std::endl;
    std::cout << territory2.getName() << " has " << territory2.getArmies() << " armies." << std::endl;

    return 0;
}
 