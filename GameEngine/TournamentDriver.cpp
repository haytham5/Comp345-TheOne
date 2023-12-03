#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include "GameEngine.h"
using namespace std;

int main()
{
    GameEngine *engine = new GameEngine();
    engine->testTournamentMode();
}