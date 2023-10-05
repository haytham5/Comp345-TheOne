#pragma once
#include "Order.h"
#include "Territory.h"

class BlockadeOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BlockadeOrder(Territory* target);
    bool validate() override;
    void execute() override;
};
