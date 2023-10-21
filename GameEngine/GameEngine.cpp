#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

typedef GameEngine::GameState GS;

//default constructor
GameEngine::GameEngine()
{
    this->state = START;
    this->processor = new CommandProcessor();
    this->gameStarted = false;
}

//copy constructor
GameEngine::GameEngine(GameEngine& gameEngine){
    this->state = gameEngine.getGameState();
}

//return current state of the game
GameEngine::GameState GameEngine::getGameState()
{
    return state;
}

//function to transition to next state
void GameEngine::transition(GS state)
{
    this->state = state;
}

//execute the state change based on which state the game is currrently in
void GameEngine::executeStateChange(string stateChange)
{
    GS state = stringToState(stateChange);

    transition(state);

    cout << "You are now in the state: " << stateToString() << "\n";
}

//function to covert enum to string
std::string GameEngine::stateToString()
{
    switch (state)
    {
    case START:
        return "START";
    case MAP_LOADED:
        return "MAP_LOADED";
    case MAP_VALIDATED:
        return "MAP_VALIDATED";
    case PLAYERS_ADDED:
        return "PLAYERS_ADDED";
    case GAME_START:
        return "GAME_START";
    case ASSIGN_REINFORCEMENT:
        return "ASSIGN_REINFORCEMENT";
    case ISSUE_ORDERS:
        return "ISSUE_ORDERS";
    case EXECUTE_ORDERS:
        return "EXECUTE_ORDERS";
    case WIN:
        return "WIN";
    case END:
        return "END";
    default:
        return "Error reading state.\n";
    }
}

//function to covert string to enum
GameEngine::GameState GameEngine::stringToState(string s)
{
    GameState gsArray[10] = {
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

    string stringArray[10] = {
        "START",
        "MAP_LOADED",
        "MAP_VALIDATED",
        "PLAYERS_ADDED",
        "ASSIGN_REINFORCEMENT",
        "GAME_START",
        "ISSUE_ORDERS",
        "EXECUTE_ORDERS",
        "WIN",
        "END"
    };

    for(int i = 0; i < sizeof(stringArray); i++) if(stringArray[i] == s) return gsArray[i];

    return END;
}

bool GameEngine::executeCommand(Command *command)
{
    string c = command->getCommand();
    string e = command->getEffect();

    //TODO: ENGINE ACTIONS BASED ON STATE (PART 2)
    //IF LOADMAP, ASK FOR MAP FILENAME

    //IF VALIDATEMAP, VALIDATE MAP

    //IF ADDPLAYER, ASK FOR PLAYER NAMES, ETC...

    //RETURN FALSE IF THERE IS PROBLEM EXECUTING COMMAND


    if(c.find("loadmap") != std::string::npos) {
        //get Map File and try to load
    }

    if(c.find("gamestart") != std::string::npos) {
        cout <<"GAMESTART";
        gameStarted = true;
    }

    if(c.find("win") != std::string::npos) {
        cout<<"WIN";
        gameStarted = false;
    }

    return true;
}

GameEngine& GameEngine::operator=(GameEngine& gameEngine) {
  this->state = gameEngine.getGameState();
  return *this;
}

ostream& operator<<(ostream& os, GameEngine& gameEngine) {
  os << "Current Game State: " << gameEngine.stateToString() << endl;
  return os;
}

void GameEngine::run()
{

    cout << "Game Started.\n" << endl;

    while (true)
    {
        string state = stateToString();
        processor->setState(&state);

        if (state == "END")
        {
            break;
        }
        else
        {
            if(gameStarted)  {
                //MAIN GAMEPLAYLOOP (PART 3)
                //Run through Players collection and call each playerprocessor
                //EXAMPLE: 
                // cout << "Player 1, enter your command: ";
            }

            cout << "Enter command to trigger state change: ";
            cin >> *processor;
            if(processor->hasNew()) {
                if(executeCommand(processor->getCommand()))
                    executeStateChange(processor->getCommand()->getEffect());
                processor->removeNew();
            }

        }
    }
    cout << "Game Over";

}

void testGameEngine()
{
    GameEngine *engine = new GameEngine();

    engine->run();
}
