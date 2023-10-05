#include "Territory.h"

// Default Constructor
Territory::Territory() 
    : name(""), locationX(0), locationY(0), continent(""), player("Unassigned"), armies(0) {
}

// Parameterized Constructor
Territory::Territory(const string& name, const int locationX, const int locationY, const string& continent) 
    : name(name), locationX(locationX), locationY(locationY), continent(continent), player("Unassigned"), armies(0) {
}

// Parameterized Constructor
Territory::Territory(const string& name, const int locationX, const int locationY, const string& continent, const string& player, int armies) 
    : name(name), locationX(locationX), locationY(locationY), continent(continent), player(player), armies(armies) {
}

// Copy Constructor
Territory::Territory(const Territory& territory) 
    : name(territory.getName()), continent(territory.getContinent()), player(territory.getPlayer()), armies(territory.getArmies()) {
}

// Destructor
Territory::~Territory() {
}



string Territory::getName() const {
    return this->name;
}

void Territory::setName(const string& name) {
    this->name = name;
}

int Territory::getLocationX() const {
    return this->locationX;
}

void Territory::setLocationX(const int locationX) {
    this->locationX = locationX;
}

int Territory::getLocationY() const {
    return this->locationY;
}

void Territory::setLocationY(const int locationY) {
    this->locationY = locationY;
}

string Territory::getContinent() const {
    return this->continent;
}

void Territory::setContinent(const string& continent) {
    this->continent = continent;
}

string Territory::getPlayer() const {
    return this->player;
}

void Territory::setPlayer(const string& player) {
    this->player = player;
}

int Territory::getArmies() const {
    return this->armies;
}

void Territory::setArmies(const int armies) {
    if (armies >= 0) {
        this->armies = armies;
    } else {
        throw invalid_argument("armies has to be a positive integer.");
    }
}

bool Territory::isNeutral() const {
    return neutral;
}

void Territory::setNeutral(bool neutralStatus) {
    neutral = neutralStatus;
}

Territory& Territory::operator=(const Territory& territory) {
    if (this != &territory) {
        this->name = territory.name;
        this->locationX = territory.locationX;
        this->locationY = territory.locationY;
        this->continent = territory.continent;
        this->player = territory.player;
        this->armies = territory.armies;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Territory& territory) {
    os << "Name: " << territory.getName()
       << "\nContinent: " << territory.getContinent() 
       << "\nOwner: " << territory.getPlayer() 
       << "\nArmies: " << territory.getArmies();
    return os;
}
