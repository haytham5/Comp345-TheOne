#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class Territory {
  private:
    string name;
    int locationX;
    int locationY;
    string continent;
    string player;
    int armies;
  public:
    Territory();
    Territory(const string& name, const int locationX, const int locationY, const string& continent);
    Territory(const string& name, const int locationX, const int locationY, const string& continent, const string& player, const int armies);
    Territory(const Territory& territory);

    ~Territory();

    string getName() const;
    void setName(const string& name);
    int getLocationX() const;
    void setLocationX(const int locationX);
    int getLocationY() const;
    void setLocationY(const int locationY);
    string getContinent() const;
    void setContinent(const string& continent);
    string getPlayer() const;
    void setPlayer(const string& player);
    int getArmies() const;
    void setArmies(const int armies);

    Territory& operator=(const Territory& territory);
};
//the operator<< overload for Territory
ostream& operator<<(std::ostream& os, const Territory& territory);

class Map {
  private:
    unordered_map<string, Territory*> territories;
    unordered_map<string, vector<string> > adjacencyList;
    vector<vector<Territory*> > territoryGrid;
   // bool addTerritory(const string& name, const int locationX, const int locationY, const string& continent);
    //bool addEdge(const string& territory1, const string& territory2);
   
    void dfs(const string& territoryName, unordered_set<string>& visited);
  public:
    
    Map();
    Map(const Map& map);

    ~Map();
    vector<Territory*> getTerritories() const;
    vector<Territory*> getTerritoriesByName(const string& name) const;
    Territory* getTerritory(const string& name) const;
    vector<string> getNeighbors(const string& name) const;
    bool initializeTerritory(const string& name, const string& player, int armies);
    bool validate();
    //////////////////////////////////////////////////
   bool addTerritory(const string& name, const int locationX, const int locationY, const string& continent);
   bool addEdge(const string& territory1, const string& territory2);
   //////////////////////////////////////////////////
    Map& operator=(const Map& map);

    friend class MapLoader;
};
//the operator<< overload for Map
ostream& operator<<(std::ostream& os, const Map& map);


class MapLoader {
  public:
    static Map loadMapFromFile(const string& filename);
    static bool isValidMapFile(const string& filename);
    static bool testAddTerritory();
    static bool testAddEdge();
};

#endif