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
    //copy constructor
    GameEngine(GameEngine& gameEngine);
    //function to get current state of game
    GameState getGameState();
    void transition(GameEngine::GameState);
    std::string stateToString();
    //function to convert states to string
    void executeStateChange(string command);

    GameEngine& operator=(GameEngine& gameEngine);

    friend ostream& operator<<(ostream& out, GameEngine& gameEngine);

private:
    //state of the game
    GameState state;
};

//test for game engine in part 5 of assignment 1
void testGameEngine();
