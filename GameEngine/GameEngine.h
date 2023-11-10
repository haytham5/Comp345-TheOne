#include <iostream>
#include <string>
#include <vector>
#include "../CommandProcessing/CommandProcessing.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

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

    void startupPhase();

    //Transition states
    void transition(GameEngine::GameState);
    
    //function to convert states to string
    std::string stateToString();
    
    //Function to convert string to state
    GameState stringToState(string s);

    //Executes command, if command needs to be executed
    bool executeCommand(Command command);

    //Changes state
    void executeStateChange(string stateChange);

    GameEngine& operator=(GameEngine& gameEngine);

    friend ostream& operator<<(ostream& os, GameEngine& gameEngine);

private:
    //Game started
    bool gameStarted;

    //state of the game
    GameState state;

    //Processor
    CommandProcessor* processor;

    FileCommandProcessorAdapter* fileProcessor;

    vector<Player*> players;
    int currentPlayerIndex;

    MapLoader* mapLoader;

    string currentMap;
};

//test for game engine in part 5 of assignment 1
void testGameEngine();
