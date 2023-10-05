#pragma once
#include "Order.h"
#include "Territory.h"

class BombOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BombOrder(Territory* target);
    bool validate() override;
    void execute() override;
};
