#include <iostream>
#include <string>
#include <vector>
#include "../CommandProcessing/CommandProcessing.h"

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
        GAME_START,
        ISSUE_ORDERS,
        EXECUTE_ORDERS,
        WIN,
        END
    };
    //default constructor
    GameEngine();
    //copy constructor
    GameEngine(GameEngine& gameEngine);

    //Run
    void run();

    //function to get current state of game
    GameState getGameState();
    //Transition states
    void transition(GameEngine::GameState);
    std::string stateToString();
    
    GameState stringToState(string s);
    //function to convert states to string
    void executeStateChange(string stateChange);

    GameEngine& operator=(GameEngine& gameEngine);

    friend ostream& operator<<(ostream& os, GameEngine& gameEngine);
private:
    //state of the game
    GameState state;

    //Processor
    CommandProcessor* processor;
};

//test for game engine in part 5 of assignment 1
void testGameEngine();
