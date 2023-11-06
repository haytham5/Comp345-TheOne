#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "GameEngine.h"
#include "../Player/Player.h"

typedef GameEngine::GameState GS;

// default constructor
GameEngine::GameEngine()
{
    this->state = START;
}

// copy constructor
GameEngine::GameEngine(GameEngine &gameEngine)
{
    this->state = gameEngine.getGameState();
}

// return current state of the game
GameEngine::GameState GameEngine::getGameState()
{
    return state;
}

// function to transition to next state
void GameEngine::transition(GS state)
{
    this->state = state;
}

// execute the state change based on which state the game is currrently in
void GameEngine::executeStateChange(string command)
{

    if (command == "loadmap" && (state == START || state == MAP_LOADED))
    {
        transition(MAP_LOADED);
    }
    else if (command == "validatemap" && state == MAP_LOADED)
    {
        transition(MAP_VALIDATED);
    }
    else if (command == "addplayer" && (state == MAP_VALIDATED || state == PLAYERS_ADDED))
    {
        transition(PLAYERS_ADDED);
    }
    else if (command == "assigncountries" && state == PLAYERS_ADDED)
    {
        transition(ASSIGN_REINFORCEMENT);
    }
    else if (command == "issueorder" && (state == ASSIGN_REINFORCEMENT || state == ISSUE_ORDERS))
    {
        transition(ISSUE_ORDERS);
    }
    else if (command == "endissueorder" && state == ISSUE_ORDERS)
    {
        transition(EXECUTE_ORDERS);
    }
    else if (command == "execorder" && state == EXECUTE_ORDERS)
    {
        transition(EXECUTE_ORDERS);
    }
    else if (command == "endexecorder" && state == EXECUTE_ORDERS)
    {
        transition(ASSIGN_REINFORCEMENT);
    }
    else if (command == "win" && state == EXECUTE_ORDERS)
    {
        transition(WIN);
    }
    else if (command == "play" && state == WIN)
    {
        transition(START);
    }
    else if (command == "end")
    {
        transition(END);
    }
    else
    {
        cout << "Error: Invalid command" << endl;
    }
    cout << "You are now in the state: " << stateToString() << "\n";
}

// function to covert enum to string
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

GameEngine &GameEngine::operator=(GameEngine &gameEngine)
{
    //   if (this != &gameEngine) {
    //     GameEngine temp(gameEngine);
    //     swap(*this, temp);
    //   }
    this->state = gameEngine.getGameState();
    return *this;
}

ostream &operator<<(ostream &os, GameEngine &gameEngine)
{
    // os << "Current Game State: " << gameEngine.stateToString << endl;
    os << "Current Game State: " << gameEngine.stateToString() << endl;
    return os;
}

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

void GameEngine::reinforcementPhase()
{
    // temporary creation of players while waiting for part 2 to be completed
    int numPlayers = 5;
    players[numPlayers];
    for (int i = 0; i < numPlayers; i++)
    {
        Player *p = new Player();
        p->setName("Player: " + i);
    }

    // temporary bool if player owns all territory of continent
    bool ownAllTerritoryInContinent = false;

    for (int i = 0; i < players.size(); i++)
    {
        cout << "Player: " << players[i]->getName() << "'s updated reinforcement pool:";
        // if the number of territories owned / 3 is less than 3, number of reinforcement army units for the player is 3
        if (((players[i]->getPlayerTerritories().size()) / 3) < 3)
        {
            // players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 3);
            // cout << players[i]->getReinforcementPool();
        }
        // else if the player owns all the territories of an entire continent, the player is given a number of army units corresponding to the continent’s control bonus value
        else if (ownAllTerritoryInContinent)
        {
            // players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 10);
            // cout << players[i]->getReinforcementPool();
        }
        else
        {
            // players[i]->setReinforcementPool(players[i]->getReinforcementPool() + ((players[i]->getPlayerTerritories().size()) / 3));
            // cout << players[i]->getReinforcementPool();
        }
    }
}