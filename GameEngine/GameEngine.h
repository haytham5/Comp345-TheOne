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
    //function to get current state of game
    GameState getGameState();
    void transition(GameEngine::GameState);
    std::string stateToString();
    //function to convert states to string
    void executeStateChange(string command);

private:
    //state of the game
    GameState state;
};