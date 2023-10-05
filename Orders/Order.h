#pragma once

#include <string>

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
