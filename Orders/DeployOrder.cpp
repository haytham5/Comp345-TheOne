#include "DeployOrder.h"

DeployOrder::DeployOrder(Territory* target, int armies)
    : targetTerritory(target), numberOfArmies(armies) {
    description = "Deploy " + std::to_string(armies) + " to " + target->getName();
}

bool DeployOrder::validate() {
    // Here you would implement the validation logic for a Deploy order.
    // This is just a mock implementation.
    return targetTerritory != nullptr && numberOfArmies > 0;
}

void DeployOrder::execute() {
    // Here you would implement the action for the Deploy order.
    // For example, increasing the number of armies in the target territory.
    // This is a mock implementation for demonstration purposes.
    if (validate()) {
        targetTerritory->setArmies(targetTerritory->getArmies() + numberOfArmies);
        isExecuted = true;
    }
}
