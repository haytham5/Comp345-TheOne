#include "BlockadeOrder.h"

BlockadeOrder::BlockadeOrder(Territory* target)
    : targetTerritory(target) {
    description = "Blockade " + target->getName();
}

bool BlockadeOrder::validate() {
    // Logic to validate the blockade order.
    return !targetTerritory->isNeutral();
}

void BlockadeOrder::execute() {
    if (validate()) {
        targetTerritory->setArmies(targetTerritory->getArmies() * 3);
        targetTerritory->setNeutral(true); // Assuming you have a setNeutral method in Territory
        isExecuted = true;
    }
}
