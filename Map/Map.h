#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
class Territory {
  private:
    string name;
    string continent;
    string player;
    int armies;
  public:
    Territory();
      Territory(const string& name, const string& continent);
    Territory(const string& name, const string& continent, const string& player, const int armies);
    Territory(const Territory& territory);

    ~Territory();

    string getName() const;
    void setName(const string& name);
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
    unordered_map<string, Territory> territories;
    unordered_map<string, vector<string>> adjacencyList;

    bool addTerritory(const string& name, const string& continent, const string& owner, int armies);
    bool addEdge(const string& territory1, const string& territory2);
  public:
    Map();
    Map(const Map& map);

    ~Map();
    
    vector<string> getTerritories() const;
    Territory getTerritory(const string& name) const;
    vector<string> getNeighbors(const string& name) const;
    bool initializeTerritory(const string& name, const string& player, int armies);
    bool validate() const;

    Map& operator=(const Map& map);

    friend class MapLoader;
};
//the operator<< overload for Map
ostream& operator<<(std::ostream& os, const Map& map);


class MapLoader {
  public:
    static Map loadMapFromFile(const string& filename);
    static bool isValidMapFile(const string& filename);
};

#endif