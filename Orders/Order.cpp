#include "Order.h"

std::string Order::getDescription() const { 
    return description; 
}

bool Order::hasExecuted() const { 
    return isExecuted; 
}