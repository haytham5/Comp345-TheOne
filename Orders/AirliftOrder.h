#pragma once
#include "Order.h"
#include "Territory.h"

class AirliftOrder : public Order {
private:
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;

public:
    AirliftOrder(Territory* source, Territory* target, int armies);
    bool validate() override;
    void execute() override;
};
