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
    Territory(const string& name, const string& continent, const string& player, const int armies);
    string getName() const;
    void setName(const string& name);
    string getContinent() const;
    void setContinent(const string& continent);
    string getPlayer() const;
    void setPlayer(const stirng& player);
    int getArmies() const;
    void setArmies(const int armies) const;
};

class Map {
  private:
    unordered_map<string, Territory> territories;
    unordered_map<string, vector<string>> adjacencyList;
    unordered_map<string, string> continentMapping;

  public:
    Map();
    bool addTerritory(const string& name, const string& continent, const string& owner, int armies);
    bool addEdge(const string& territory1, const string& territory2);
    bool setContinent(const string& territory, const string& continent);
    bool validate() const;

    friend class MapLoader;
};

class MapLoader {
  public:
    static Map loadMapFromFile(const string& filename);
    static bool isValidMapFile(const string& filename);
};

#endif