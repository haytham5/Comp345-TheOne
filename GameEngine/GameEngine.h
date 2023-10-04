#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GameEngine
{
public:
    //different states the game can be in
    enum GameState
    {
        START,
        MAP_LOADED,
        MAP_VALIDATED,
        PLAYERS_ADDED,
        ASSIGN_REINFORCEMENT,
        ISSUE_ORDERS,
        EXECUTE_ORDERS,
        WIN,
        END
    };
    //default constructor
    GameEngine();
    GameState getGameState();
    void transition(GameEngine::GameState);
    std::string stateToString();
    void executeStateChange(string command);

private:
    GameState state;
};