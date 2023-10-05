#pragma once
#include "Order.h"
#include "Territory.h"

class AdvanceOrder : public Order {
private:
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;

public:
    AdvanceOrder(Territory* source, Territory* target, int armies);
    bool validate() override;
    void execute() override;
};
