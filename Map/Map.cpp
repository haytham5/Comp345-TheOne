#include "Map.h"

#include <iostream>
#include <stdexcept>

Territory::Territory(){
}

Territory::Territory(const string& name, const string& continent)
  : name(name), continent(continent), player("Unassigned"), armies(0) {
}

Territory::Territory(const string& name, const string& continent, const string& player, int armies)
  : name(name), continent(continent), player(player), armies(armies) {
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

Map::Map(const Map& map) {
  for (const auto& pair : map.territories) {
    this->territories[pair.first] = Territory(pair.second);
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
}

bool Map::addTerritory(const string& name, const string& continent, const string& player, int armies){
  auto iter = territories.find(name);

  if (iter != territories.end()) {
    cout << "Territory with name " << name << " already exists." << endl;
    return false;
  }
  Territory newTerritory = Territory(name, continent);
  this->territories[name] = newTerritory;
  cout << "Territory " << name << " added successfully." << endl;
  return true;
}

bool Map::addEdge(const string& territory1, const string& territory2){
  this->adjacencyList[territory1].push_back(territory2);
  this->adjacencyList[territory2].push_back(territory1);
  return true;
}

vector<string> Map::getTerritories() const {
  vector<string> territoryNames;   
  for (const auto& pair : territories) {
      territoryNames.push_back(pair.first); // pair.first is the territory name
  }
  return territoryNames;
}

Territory Map::getTerritory(const string& name) const {
  auto it = this->territories.find(name);
  if (it != this->territories.end()) {
      return it->second;
  } else {
      throw std::out_of_range("Territory not found");
  }
}

vector<string> Map::getNeighbors(const std::string& name) const {
  auto it = this->adjacencyList.find(name);
  if (it != this->adjacencyList.end()) {
      return it->second;
  } else {
      throw std::out_of_range("Territory not found");
  }
}

bool Map::initializeTerritory(const string& name, const string& player, int armies){
  auto it = this->territories.find(name);
  if (it != this->territories.end()) {
      it->second.setPlayer(player);
      it->second.setArmies(armies);
      return true;
  } else {
      throw std::out_of_range("Territory not found");
  }
}

bool Map::validate() const {
  // TODO
}

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