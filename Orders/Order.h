#pragma once
#include <string>
#include <vector>
#include "../Map/Map.h"  // Assuming Territory is in a separate file named Territory.h

void testOrdersList();

class Order {
protected:
    std::string description;
    bool isExecuted = false;

public:
    virtual bool validate() = 0; // Check if the order is valid.
    virtual void execute() = 0; // Execute the order action.
    virtual ~Order() {} // Virtual destructor to ensure proper cleanup for derived classes.
    
    Order& operator = (const Order& other) {
        description = other.description;
        isExecuted = other.isExecuted;
        return *this;
    }

    //Ostream
    friend ostream & operator << (ostream &out, const Order &object) {
        out << object.description << "; Executed: " << object.isExecuted << endl;
        return out;
    }

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

    OrdersList& operator = (const OrdersList& other) {
        orders = other.orders;
        return *this;
    }
    
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

    DeployOrder& operator = (const DeployOrder& other) {
        description = other.description;
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        numberOfArmies = other.numberOfArmies;
        return *this;
    }

    //Ostream
    friend ostream & operator << (ostream &out, const DeployOrder &object) {
        out << object.description << "; Executed: " << 
        object.isExecuted << "; Target Territory: " << 
        object.targetTerritory << "; Number of Armies: " <<
        object.numberOfArmies << endl;
        return out;
    }

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

    AdvanceOrder& operator = (const AdvanceOrder& other) {
        description = other.description;
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        sourceTerritory = other.sourceTerritory;
        numberOfArmies = other.numberOfArmies;
        return *this;
    }

    //Ostream
    friend ostream & operator << (ostream &out, const AdvanceOrder &object) {
        out << object.description << "; Executed: " << 
        object.isExecuted << "; Target Territory: " << 
        object.targetTerritory << "; Source Territory : " << 
        object.sourceTerritory << "; Number of Armies: " <<
        object.numberOfArmies << endl;
        return out;
    }

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

    AirliftOrder& operator = (const AirliftOrder& other) {
        description = other.description;
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        sourceTerritory = other.sourceTerritory;
        numberOfArmies = other.numberOfArmies;
        return *this;
    }

    //Ostream
    friend ostream & operator << (ostream &out, const AirliftOrder &object) {
        out << object.description << "; Executed: " << 
        object.isExecuted << "; Target Territory: " << 
        object.targetTerritory << "; Source Territory : " << 
        object.sourceTerritory << "; Number of Armies: " <<
        object.numberOfArmies << endl;
        return out;
    }

    bool validate() override;
    void execute() override;
};

class BlockadeOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BlockadeOrder();
    BlockadeOrder(Territory* target);

    BlockadeOrder& operator = (const BlockadeOrder& other) {
        description = other.description;
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        return *this;
    }

    //Ostream
    friend ostream & operator << (ostream &out, const BlockadeOrder &object) {
        out << object.description << "; Executed: " << 
        object.isExecuted << "; Target Territory: " << 
        object.targetTerritory << "; Source Territory : " << endl;
        return out;
    }
    

    bool validate() override;
    void execute() override;
};

class BombOrder : public Order {
private:
    Territory* targetTerritory;

public:
    BombOrder();
    BombOrder(Territory* target);

    BombOrder& operator = (const BombOrder& other) {
        description = other.description;
        isExecuted = other.isExecuted;
        targetTerritory = other.targetTerritory;
        return *this;
    }

    //Ostream
    friend ostream & operator << (ostream &out, const BombOrder &object) {
        out << object.description << "; Executed: " << 
        object.isExecuted << "; Target Territory: " << 
        object.targetTerritory << "; Source Territory : " << endl;
        return out;
    }

    bool validate() override;
    void execute() override;
};