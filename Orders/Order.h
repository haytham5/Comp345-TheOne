#pragma once
#include <string>
#include <vector>
#include "../Map/Map.h"  // Assuming Territory is in a separate file named Territory.h
#include "../LoggingObserver/LoggingObserver.h"

void testOrdersList();
void testOrderExecution();

class Order : public ILoggable, public Subject{
protected:
    std::string description;
    bool isExecuted = false;

public:
    virtual bool validate() = 0; // Check if the order is valid.
    virtual void execute() = 0; // Execute the order action.
    virtual ~Order() {} // Virtual destructor to ensure proper cleanup for derived classes.
    
    Order& operator = (const Order& other);

    //Ostream
    friend ostream & operator << (ostream &out, const Order &object);

    std::string getDescription() const;
    bool hasExecuted() const;

    virtual string stringToLog() override;
};

class OrdersList : public ILoggable, public Subject {
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

    OrdersList& operator = (const OrdersList& other);
    
    // Getters
    const std::vector<Order*>& getOrders() const;

    // Overload stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const OrdersList& ordersList);

    virtual string stringToLog() override;
};


class DeployOrder : public Order {
private:
    Territory* targetTerritory;
    int numberOfArmies;
    std::string issuingPlayer; //The player issuing the order

public:
    // Constructor
    DeployOrder();
    DeployOrder(Territory* target, int armies, const std::string& player); //adds the player to the constructor

    DeployOrder& operator = (const DeployOrder& other);

    //Ostream
    friend ostream & operator << (ostream &out, const DeployOrder &object);

    // Overridden functions from the base Order class
    bool validate() override;
    void execute() override;
};

class AdvanceOrder : public Order {
private:
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;
    //Pointer to the map object
    Map* gameMap;
    std::string issuingPlayer; //The player issuing the order

public:
    AdvanceOrder();
    AdvanceOrder(Territory* source, Territory* target, int armies, Map* gameMap, const std::string& player);

    AdvanceOrder& operator = (const AdvanceOrder& other);

    //Ostream
    friend ostream & operator << (ostream &out, const AdvanceOrder &object);

    bool validate() override;
    void execute() override;
};

class AirliftOrder : public Order {
private:
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int numberOfArmies;
     std::string issuingPlayer;  // The player issuing the order

public:
    AirliftOrder();
    AirliftOrder(Territory* source, Territory* target, int armies, const std::string& player);

    AirliftOrder& operator = (const AirliftOrder& other);

    //Ostream
    friend ostream & operator << (ostream &out, const AirliftOrder &object);


    bool validate() override;
    void execute() override;
};

class BlockadeOrder : public Order {
private:
    Territory* targetTerritory;
    std::string issuingPlayer;  

public:
    BlockadeOrder();
    BlockadeOrder(Territory* target, const std::string& player);

    BlockadeOrder& operator = (const BlockadeOrder& other);
    //Ostream
    friend ostream & operator << (ostream &out, const BlockadeOrder &object);

    bool validate() override;
    void execute() override;
};

class BombOrder : public Order {
private:
    Territory* targetTerritory;
    std::string issuingPlayer;  // The player issuing the order
    Map* gameMap;  // Map object to check adjacency

public:
    BombOrder();
    BombOrder(Territory* target, const std::string& player, Map* gameMap);

    BombOrder& operator = (const BombOrder& other);

    //Ostream
    friend ostream & operator << (ostream &out, const BombOrder &object);

    bool validate() override;
    void execute() override;
};