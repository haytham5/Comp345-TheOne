#include "AdvanceOrder.h"


AdvanceOrder::AdvanceOrder(Territory* source, Territory* target, int armies)
    : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies) {
    description = "Advance " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName();
}

bool AdvanceOrder::validate() {
    // Logic to validate the advance order.
    // For example, the source territory must have enough armies to advance.
    return sourceTerritory->getArmies() >= numberOfArmies;
}

void AdvanceOrder::execute() {
    if (validate()) {
        sourceTerritory->setArmies(sourceTerritory->getArmies() - numberOfArmies);
        targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        isExecuted = true;
    }
}
