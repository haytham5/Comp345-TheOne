#pragma once

#include <vector>
#include "Order.h"

class OrdersList {
private:
    std::vector<Order*> orders;

public:
    OrdersList();  // Constructor
    OrdersList(const OrdersList& other);  // Copy constructor
    ~OrdersList();  // Destructor

    // Methods
    void addOrder(Order* order);
    void removeOrder(Order* order);
    void moveOrder(int fromIndex, int toIndex);
    
    // Getters
    const std::vector<Order*>& getOrders() const;

    // Overload stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);
};
