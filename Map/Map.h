#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
class Territory {
  public:
    Territory();
    Territory(const string& name, const string& continent, const string& owner, const int armies);
    string name;
    string continent;
    string owner;
    int armies;
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
    // Other methods for map operations

    friend class MapLoader;
};

class MapLoader {
  public:
    static Map loadMapFromFile(const string& filename);
    static bool isValidMapFile(const string& filename);
};

#endif