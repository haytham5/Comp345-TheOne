#pragma once
#include <string>
#include <vector>
#include "..\Map\Map.h"  // Assuming Territory is in a separate file named Territory.h

class Order {
protected:
    std::string description;
    bool isExecuted = false;

public:
    virtual bool validate() = 0; // Check if the order is valid.
    virtual void execute() = 0; // Execute the order action.
    virtual ~Order() {} // Virtual destructor to ensure proper cleanup for derived classes.
    
    std::string getDescription() const;
    bool hasExecuted() const;
};

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


class DeployOrder : public Order {
private:
    Territory* targetTerritory;
    int numberOfArmies;

public:
    // Constructor
    DeployOrder();
    DeployOrder(Territory* target, int armies);

    // Overridden functions from the base Order class
    bool validate() override;
    void execute() override;
};

class AdvanceOrder : public Order {
private:
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;

public:
    AdvanceOrder();
    AdvanceOrder(Territory* source, Territory* target, int armies);
    bool validate() override;
    void execute() override;
};

class AirliftOrder : public Order {
private:
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;

public:
    AirliftOrder();
    AirliftOrder(Territory* source, Territory* target, int armies);
    bool validate() override;
    void execute() override;
};

class BlockadeOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BlockadeOrder();
    BlockadeOrder(Territory* target);
    bool validate() override;
    void execute() override;
};

class BombOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BombOrder();
    BombOrder(Territory* target);
    bool validate() override;
    void execute() override;
};