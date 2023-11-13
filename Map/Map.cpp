#define GRID_SIZE 100

#include "Map.h"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

Territory::Territory(){
  player = "TEST";
}

Territory::Territory(const string& name, const int locationX, const int locationY, const string& continent)
  : name(name), locationX(locationX), locationY(locationY), continent(continent), player("Unassigned"), armies(0) {
}

Territory::Territory(const string& name, const int locationX, const int locationY, const string& continent, const string& player, int armies)
  : name(name), locationX(locationX), locationY(locationY), continent(continent), player(player), armies(armies) {
}

Territory::Territory(const Territory& territory)
  : name(territory.getName()), continent(territory.getContinent()), player(territory.player), armies(territory.getArmies()) {
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

string Territory::getPlayer() {
  cout << player << endl;
  return player;
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
      << "\nOwner: " << territory.player
      << "\nArmies: " << territory.getArmies();
  return os;
}

Map::Map() 
 : territories(), adjacencyList(), territoryGrid(GRID_SIZE, vector<Territory*>(GRID_SIZE, nullptr)) {
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
  cout << "Deleting Map..."<<endl;
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
  int newSizeX = max(locationX + 1, static_cast<int>(territoryGrid.size()));
  int newSizeY = max(locationY + 1, static_cast<int>(territoryGrid[0].size()));

  if (newSizeX > territoryGrid.size()) {
    territoryGrid.resize(newSizeX, vector<Territory*>(territoryGrid[0].size(), nullptr));
  }

  if (newSizeY > territoryGrid[0].size()) {
    for (int i = 0; i < territoryGrid.size(); ++i) {
      territoryGrid[i].resize(newSizeY, nullptr);
    }
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
  vector<string> territory1Neighbors = this->adjacencyList[territory1];
  auto it = find(territory1Neighbors.begin(), territory1Neighbors.end(), territory2);
  if (it != territory1Neighbors.end()) {
    cout << "Cannot add edge between " << territory1 << " and " << territory2 << " as they are already neighbors." << endl;
    return false;
  }

  vector<string> territory2Neighbors = this->adjacencyList[territory2];
  it = find(territory2Neighbors.begin(), territory2Neighbors.end(), territory1);
  if (it != territory2Neighbors.end()) {
    cout << "Cannot add edge between " << territory1 << " and " << territory2 << " as they are already neighbors." << endl;
    return false;
  }

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
    return nullptr;
  }
}

vector<string> Map::getNeighbors(const string& territoryName) const {
  auto it = this->adjacencyList.find(territoryName);
  if (it != this->adjacencyList.end()) {
    return it->second;
  } else {
    return vector<string>();
  }
}

void Map::dfs(const string& territoryName, unordered_set<string>& visited) {
    visited.insert(territoryName);
    for (const auto& neighbor : adjacencyList[territoryName]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, visited);
        }
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

bool Map::validate() {
  unordered_set<string> visited;
    for (const auto& entry : territories) {
      const string& territoryName = entry.first;
      visited.clear();
      dfs(territoryName, visited);
      if (visited.size() != territories.size()) {
        cout << "There are stranded territories starting from: " << territoryName << endl;
        return false;
      }
    }

  for(const auto& entry: adjacencyList){
    const string& territoryName = entry.first;
    Territory* territoryptr = getTerritory(territoryName);
    if(territoryptr == nullptr){
      cout << "There is a territory in the adjacency list that does not exist: " << territoryName << endl;
      return false;
    }
    if(territoryptr->getContinent() == ""){
      cout << "There is a territory in the adjacency list that does not have a continent: " << territoryName << endl;
      return false;
    }
  }
  return true;
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

Map MapLoader::loadMapFromFile(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    throw runtime_error("Error: Unable to open file " + filename);
  }

  string line;
  string section;
  Map map = Map();

  while (getline(file, line)) {
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

    istringstream rowss(line);
    string key;

    if (getline(rowss, key, '=')) {
      if (key == "[Map]") {
        section = "Map";
      } else if (key == "[Continents]") {
        section = "Continents";
      } else if (key == "[Territories]") {
        section = "Territories";
      } else {
        if (section == "Map") {

        } else if (section == "Continents") {

        } else if (section == "Territories") {
          string value;
          istringstream territoryss(key);
          getline(territoryss, value, ',');
          string territoryName = value;
          getline(territoryss, value, ',');
          int x = stoi(value);
          getline(territoryss, value, ',');
          int y = stoi(value);
          getline(territoryss, value, ',');
          string continentName = value;
          map.addTerritory(territoryName, x, y, continentName);

          string neighborName;

          while (getline(territoryss, neighborName, ',')) {
            map.addEdge(territoryName, neighborName);
          }
        }
      }
    }
  }
  file.close();
  return map;
}

bool MapLoader::isValidMapFile(const string& filename) {
  Map testMap = MapLoader::loadMapFromFile(filename);
  return testMap.validate();
}

bool MapLoader::testAddTerritory(){
  Map mockMap = Map();
  bool valid = mockMap.addTerritory("Canada", 0, 0, "North America") &&
  mockMap.addTerritory("USA", 0, 1, "North America") &&
  mockMap.addTerritory("Mexico", 0, 2, "North America") &&
  mockMap.addTerritory("Brazil", 1, 0, "South America") &&
  mockMap.addTerritory("Argentina", 1, 1, "South America") &&
  mockMap.addTerritory("Peru", 1, 2, "South America") &&
  !mockMap.addTerritory("USA", 5, 1, "North America") && //Used Name
  !mockMap.addTerritory("Alaska", 0, 1, "North America") && //Overlaps locationY
  !mockMap.addTerritory("Alaska", 1, 0, "North America") && //Overlaps locationX
  !mockMap.addTerritory("Alaska", -1, 0, "North America") && //Invalid locationX
  !mockMap.addTerritory("Alaska", 0, -1, "North America"); //Invalid locationY

  return valid;
}

bool MapLoader::testAddEdge(){
  Map mockMap = Map();
  mockMap.addTerritory("Canada", 0, 0, "North America");
  mockMap.addTerritory("USA", 0, 1, "North America");
  mockMap.addTerritory("Mexico", 0, 2, "North America");
  mockMap.addTerritory("Brazil", 1, 0, "South America");
  mockMap.addTerritory("Argentina", 1, 1, "South America");

  bool valid = mockMap.addEdge("Canada", "USA") &&
  mockMap.addEdge("USA", "Mexico") &&
  mockMap.addEdge("Mexico", "Brazil") &&
  mockMap.addEdge("Brazil", "Argentina") &&
  !mockMap.addEdge("Canada", "Canada") && //Same territory
  !mockMap.addEdge("Canada", "USA"); //Already neighbors

  return valid;
}


bool testLoadMaps(){
  bool valid = true;
  valid = valid && MapLoader::isValidMapFile("resources/ABC_Map.map");
  valid = valid && MapLoader::isValidMapFile("resources/Asia.map");
  valid = valid && !MapLoader::isValidMapFile("resources/ABC_MapInvalid.map"); //Invalid Map
  if(valid){
    std::cout << "All test passed!" << endl;
    return true;
  }

  cout << "Tests failed!" << endl;
  return false;
}