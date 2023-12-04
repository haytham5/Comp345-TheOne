#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Territory Class
class Territory {
  private:
    string name;
    int locationX;
    int locationY;
    string continent;
    string player;
    int armies;
  public:
    // Constructors
    Territory();
    Territory(const string& name, const int locationX, const int locationY, const string& continent);
    Territory(const string& name, const int locationX, const int locationY, const string& continent, const string& player, const int armies);
    Territory(const Territory& territory);

    // Destructor
    ~Territory();

    // Getter and setter functions for territory attributes
    string getName() const;
    void setName(const string& name);
    int getLocationX() const;
    void setLocationX(const int locationX);
    int getLocationY() const;
    void setLocationY(const int locationY);
    string getContinent() const;
    void setContinent(const string& continent);
    string getPlayer();
    void setPlayer(const string& player);
    int getArmies() const;
    void setArmies(const int armies);

    void setNeighbours(string Territory1, string Territory2);

    // Assignment operator for Territory class
    Territory& operator=(const Territory& territory);

    friend ostream& operator<<(std::ostream& os, const Territory& territory);
};

// Overload the << operator for Territory to allow printing


// Map Class
class Map {
  private:
    unordered_map<string, Territory*> territories;
    vector<Territory> territoryVector;
    unordered_map<string, vector<string> > adjacencyList;
    vector<vector<Territory*> > territoryGrid;

    void dfs(const string& territoryName, unordered_set<string>& visited);
  public:
    // Constructors
    Map();
    Map(const Map& map);

    // Destructor
    ~Map();

    // Functions to add edges and territories to the map
    bool addEdge(const string& territory1, const string& territory2);
    bool addTerritory(const string& name, const int locationX, const int locationY, const string& continent);

    // Functions to retrieve information about territories and neighbors
    vector<Territory*> getTerritories() const;
    Territory getTerritoryAt(int i);
    vector<Territory*> getTerritoriesByName(const string& name) const;
    vector<Territory*> getAllTerritoriesByName();
    Territory* getTerritory(const string& name) const;
    vector<string> getNeighbors(const string& name) const;
    vector<Territory*> getNeighborsPointers(const string& territoryName) const;

    // Initialize a territory with player ownership and armies
    bool initializeTerritory(const string& name, const string& player, int armies);

    // Validate the map
    bool validate();

    // Assignment operator for Map class
    Map& operator=(const Map& map);

    // Friend class MapLoader for loading maps from files
    friend class MapLoader;
};

// Overload the << operator for Map to allow printing
ostream& operator<<(std::ostream& os, const Map& map);

// Class for loading maps from files and testing map functions
class MapLoader {
  public:
    // Load a map from a file
    static Map loadMapFromFile(const string& filename);

    vector<Territory*> loadMapVectorFromFile(const string& filename);

    // Check if a map file is valid
    static bool isValidMapFile(const string& filename);

    // Test adding territories to the map
    static bool testAddTerritory();

    // Test adding edges between territories
    static bool testAddEdge();
};

// Test function for loading maps
bool testLoadMaps();

#endif