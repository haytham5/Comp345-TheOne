#include "Map.h"

#include <iostream>

int main() {
  
  Map myMap = Map(1000, 1000);
  myMap.addTerritory("Canada", 0, 0, "North America");
  myMap.addTerritory("USA", 0, 1, "North America");
  myMap.addTerritory("Mexico", 0, 2, "North America");
  myMap.addTerritory("Brazil", 1, 0, "South America");
  myMap.addTerritory("Argentina", 1, 1, "South America");
  myMap.addTerritory("Peru", 1, 2, "South America");
  myMap.addTerritory("Greenland", 2, 0, "North America");
  myMap.addTerritory("Iceland", 2, 1, "Europe");
  myMap.addTerritory("UK", 2, 2, "Europe");
  myMap.addTerritory("France", 3, 0, "Europe");
  myMap.addTerritory("Spain", 3, 1, "Europe");
  myMap.addTerritory("Germany", 3, 2, "Europe");

  myMap.addTerritory("USA", 5, 1, "North America");
  myMap.addTerritory("Alaska", 0, 1, "North America");

  myMap.addEdge("Canada", "USA");
  myMap.addEdge("USA", "Mexico");
  myMap.addEdge("Canada", "Greenland");
  myMap.addEdge("Greenland", "Iceland");
  myMap.addEdge("Iceland", "UK");
  myMap.addEdge("UK", "France");
  myMap.addEdge("France", "Spain");
  myMap.addEdge("Spain", "Germany");
  myMap.addEdge("Germany", "UK");
  myMap.addEdge("Canada", "USA");
  

  for (auto neighbors : myMap.getNeighbors("USA")) {
    std::cout << neighbors << " ";
  }
  cout << endl << myMap;
  return 0;
}