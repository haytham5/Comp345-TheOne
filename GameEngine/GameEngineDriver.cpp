#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include "GameEngine.h"
using namespace std;

//test for game engine in part 5 of assignment 1
void testGameEngine()
{
    GameEngine *engine = new GameEngine();
    cout << "The game is currently in the " << engine->stateToString() << " state\n";

    string state = engine->stateToString();
    while (true)
    {
        string state = engine->stateToString();
        if (state == "END")
        {
            break;
        }
        else
        {
            string command;
            cout << "Enter command to trigger state change: ";
            cin >> command;
            engine->executeStateChange(command);
        }
    }
    cout << "Game Over";
}

int main()
{
    testGameEngine();

    return 0;
}