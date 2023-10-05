#include "Order.h"
#include "Territory.h"

class BombOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BombOrder(Territory* target) : targetTerritory(target) {
        description = "Bomb " + target->getName();
    }

    bool validate() override {
        // Simple validation: Target territory must have armies.
        return targetTerritory->getArmies() > 0;
    }

    void execute() override {
        if (validate()) {
            targetTerritory->setArmies(targetTerritory->getArmies() / 2);  // Reduce armies by half as an example effect of bombing.
            isExecuted = true;
        }
    }
};
