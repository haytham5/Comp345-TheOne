#include "OrdersList.h"
#include "Order.h"
#include <iostream>
#include "DeployOrder.h"

// Constructor
OrdersList::OrdersList() {}

// Copy constructor
OrdersList::OrdersList(const OrdersList& other) {
    for (Order* order : other.orders) {
        // Deep copy: create a new order and copy its content.
        this->orders.push_back(new DeployOrder(*dynamic_cast<DeployOrder*>(order)));
    }
}

// Destructor
OrdersList::~OrdersList() {
    for (Order* order : orders) {
        delete order;
    }
    orders.clear();
}

// Methods
void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
}

void OrdersList::removeOrder(Order* order) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (*it == order) {
            delete *it;  // Free the memory of the order object
            orders.erase(it);  // Remove the pointer from the list
            return;
        }
    }
}

void OrdersList::moveOrder(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= orders.size() || toIndex < 0 || toIndex >= orders.size()) {
        throw std::out_of_range("Index out of range.");
    }
    std::iter_swap(orders.begin() + fromIndex, orders.begin() + toIndex);
}

const std::vector<Order*>& OrdersList::getOrders() const {
    return orders;
}

std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList) {
    for (const Order* order : ordersList.orders) {
        os << order->getDescription() << "\n";
    }
    return os;
}
