#include "Map.h"

#include <iostream>
#include <cstdio>

bool testLoadMaps();

int main() {
  testLoadMaps();

  return 0;
}

bool testLoadMaps(){
  bool valid = true;
  valid = valid && MapLoader::isValidMapFile("Map/resources/ABC_Map.map");
  valid = valid && MapLoader::isValidMapFile("Map/resources/Asia.map");
  valid = valid && !MapLoader::isValidMapFile("Map/resources/ABC_MapInvalid.map"); //Invalid Map
  if(valid){
    cout << "All test passed!" << endl;
    return true;
  }

  cout << "Tests failed!" << endl;
  return false;
}