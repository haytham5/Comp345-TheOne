#include <iostream>
#include <iostream>
#include <string>

#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"

using namespace std;


int main() {
    GameEngine *engine = new GameEngine();
    
    engine->run();
 
    return 0;
}