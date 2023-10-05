#include "AirliftOrder.h"

AirliftOrder::AirliftOrder(Territory* source, Territory* target, int armies)
    : sourceTerritory(source), targetTerritory(target), numberOfArmies(armies) {
    description = "Airlift " + std::to_string(armies) + " from " + source->getName() + " to " + target->getName();
}

bool AirliftOrder::validate() {
    // Logic to validate the airlift order.
    return sourceTerritory->getArmies() >= numberOfArmies;
}

void AirliftOrder::execute() {
    if (validate()) {
        sourceTerritory->setArmies(sourceTerritory->getArmies() - numberOfArmies);
        targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        isExecuted = true;
    }
}
