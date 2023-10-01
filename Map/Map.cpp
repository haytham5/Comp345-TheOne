#include "Map.h"

#include <iostream>
#include <stdexcept>

Territory::Territory(){
}

Territory::Territory(const string& name, const int locationX, const int locationY, const string& continent)
  : name(name), locationX(locationX), locationY(locationY), continent(continent), player("Unassigned"), armies(0) {
}

Territory::Territory(const string& name, const int locationX, const int locationY, const string& continent, const string& player, int armies)
  : name(name), locationX(locationX), locationY(locationY), continent(continent), player(player), armies(armies) {
}

Territory::Territory(const Territory& territory)
  : name(territory.getName()), continent(territory.getContinent()), player(territory.getPlayer()), armies(territory.getArmies()) {
}

Territory::~Territory(){
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

void Territory::setLocationX(const int locationX){
  this->locationX = locationX;
}

int Territory::getLocationY() const {
  return this->locationY;
}

void Territory::setLocationY(const int locationY){
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
  if (armies >= 0){
    this->armies = armies;
  }
  else {
    throw invalid_argument("armies has to be a positive integer.");
  }
}

Territory& Territory::operator=(const Territory& territory) {
  if (this != &territory) {
    Territory temp(territory);
    swap(*this, temp);
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

Map::Map() 
 : territories(), adjacencyList() {
}

Map::Map(int gridSizeX, int gridSizeY)
 : territoryGrid(gridSizeX, vector<Territory*>(gridSizeY, nullptr)), territories(), adjacencyList() {
}

Map::Map(const Map& map) {
  for (const auto& pair : map.territories) {
    this->territories[pair.first] = new Territory(*pair.second);
  }

  //TODO : Test if deep copies properly
  for (const auto& pair : map.adjacencyList) {
    const string& territory = pair.first;
    const vector<string>& neighbors = pair.second;

    vector<string> newNeighbors(neighbors.begin(), neighbors.end());
    adjacencyList[territory] = newNeighbors;
  }
}

Map::~Map() {
  for (auto row : territoryGrid) {
    for (Territory* territoryPtr : row) {
      delete territoryPtr;
    }
  }
  territoryGrid.clear();
  territories.clear();
}

bool Map::addTerritory(const string& name, const int locationX, const int locationY, const string& continent){
  auto iter = this->territories.find(name);

  if (iter != this->territories.end()) {
    cout << "Territory with name " << name << " already exists." << endl;
    return false;
  }
  if (locationX >= 0 && locationX < this->territoryGrid.size() && locationY >= 0 && locationY < this->territoryGrid[0].size()) {
    if (this->territoryGrid[locationX][locationY] != nullptr) {
      cout << "Cannot add territory at coordinates (" << locationX << ", " << locationY << ") as it overlaps with existing territory " << this->territoryGrid[locationX][locationY]->getName() << endl;
      return false;
    }
    Territory* newTerritory = new Territory(name, locationX, locationY, continent);
    this->territoryGrid[locationX][locationY] = newTerritory;
    this->territories[name] = newTerritory;
    cout << "Territory " << name << " added successfully at coordinates (" << locationX << ", " << locationY << ")." << std::endl;
    return true;
  } else {
    cout << "Invalid coordinates (" << locationX << ", " << locationY << ")." << std::endl;
    return false;
  }
  return true;
}

bool Map::addEdge(const string& territory1, const string& territory2){
  if (territory1 == territory2) {
    cout << "Cannot add edge between " << territory1 << " and " << territory2 << " as they are the same territory." << endl;
    return false;
  }
  // TODO: validate that the edge does not already exist
  this->adjacencyList[territory1].push_back(territory2);
  this->adjacencyList[territory2].push_back(territory1);
  return true;
}
vector<Territory*> Map::getTerritories() const {
  vector<Territory*> territoryNames;   
  for (const auto& pair : territories) {
      territoryNames.push_back(pair.second); // pair.first is the territory name
  }
  return territoryNames;
}

vector<Territory*> Map::getTerritoriesByName(const string& name) const {
  vector<Territory*> territoryNames;   
  for (const auto& pair : territories) {
    if(pair.second->getName() == name){
      territoryNames.push_back(pair.second); // pair.first is the territory name
    }
  }
  return territoryNames;
}

Territory* Map::getTerritory(const string& name) const {
  auto it = this->territories.find(name);
  if (it != this->territories.end()) {
    return it->second;
  } else {
    throw out_of_range("Territory not found");
  }
}

vector<string> Map::getNeighbors(const string& territoryName) const {
  auto it = this->adjacencyList.find(territoryName);
  if (it != this->adjacencyList.end()) {
    return it->second;
  } else {
    throw out_of_range("Territory not found");
  }
}

bool Map::initializeTerritory(const string& name, const string& player, int armies){
  auto it = this->territories.find(name);
  if (it != this->territories.end()) {
    it->second->setPlayer(player);
    it->second->setArmies(armies);
    return true;
  } else {
    throw out_of_range("Territory not found");
  }
}

// bool Map::validate() const {
//   // TODO
//   // Validate that all edges are pointing a real territory
// }

Map& Map::operator=(const Map& map){
  if (this != &map) {
    Map temp(map);
    swap(*this, temp);
  }
  return *this;
}

ostream& operator<<(ostream& os, const Map& map) {
  os << "Number of Territories: " << map.getTerritories().size();
  return os;
}