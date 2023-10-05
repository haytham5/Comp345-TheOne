#pragma once

#include "Order.h"
#include "Territory.h"  // Assuming Territory is in a separate file named Territory.h

class DeployOrder : public Order {
private:
    Territory* targetTerritory;
    int numberOfArmies;

public:
    // Constructor
    DeployOrder(Territory* target, int armies);

    // Overridden functions from the base Order class
    bool validate() override;
    void execute() override;
};
