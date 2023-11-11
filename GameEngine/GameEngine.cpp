#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

typedef GameEngine::GameState GS;

//default constructor
GameEngine::GameEngine()
{
    this->state = START;

    this->gameStarted = false;

    this->mapLoader = new MapLoader();
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

void GameEngine::startupPhase() {
    std::cout << "Startup Phase\n";
    while(!this->gameStarted) {
        cout << "Enter command to trigger state change: ";
        if(processor != NULL) {
            cin >> *processor;
            
            if(processor->hasNew()) {
                if(executeCommand(processor->getCommand()))
                    executeStateChange(processor->getCommand().getEffect());
                processor->removeNew();
            }
        }

        else {
            cin >> *fileProcessor;
            
            if(fileProcessor->hasNew()) {
                
                if(executeCommand(fileProcessor->getCommand()))
                    executeStateChange(fileProcessor->getCommand().getEffect());
                    
                fileProcessor->removeNew();
            }
        }
    }
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

bool GameEngine::executeCommand(Command command)
{
    string c = command.getCommand();
    string e = command.getEffect();

    //TODO: ENGINE ACTIONS BASED ON STATE (PART 2)
    //IF LOADMAP, ASK FOR MAP FILENAME

    //IF VALIDATEMAP, VALIDATE MAP

    //IF ADDPLAYER, ASK FOR PLAYER NAMES, ETC...

    //RETURN FALSE IF THERE IS PROBLEM EXECUTING COMMAND


    if(c == "loadmap") {
        // string map_name;
        // //Ask for map filename and try to load
        // cout << "Enter map filename: ";
        // cin >> map_name;
        // try{
        //     map = mapLoader->loadMapFromFile(map_name);
        //     this->currentMap = map_name;
        //     cout << map_name << " loaded." << endl;
        // }
        // catch(const char* msg){
        //     cout << "Unable to load map" << endl;
        //     return false;
        // }
    }

    if(c == "validatemap") {
        // if(mapLoader->isValidMapFile(currentMap)){
        //     cout << currentMap << " is valid." << endl;
        // }
        // else{
        //     cout << currentMap << " is invalid." << endl;
        // }
    }

    if(c == "addplayer") {
        if (currentPlayerIndex != 5) {
        string playerName;
        cout << "Enter the player name: ";
        cin >> playerName;

        // Check if the player name already exists
        bool nameExists = false;
        for (const auto& player : players) {
            if (player->getName() == playerName) {
                nameExists = true;
                break;
            }
        }

        if (!nameExists) {
            players.push_back(new Player(playerName, nullptr, nullptr, nullptr));
            currentPlayerIndex++;
            cout << "Player " << playerName << " added." << endl;
        } else {
            cout << "Player with the name " << playerName << " already exists." << endl;
        }
    } else {
        cout << "Max number of players reached." << endl;
}

    }

    if(c == "gamestart") {
        // Get the list of territories from the map
        vector<Territory*> allTerritories = map.getTerritories();

        // Seed for random number generation
        std::default_random_engine rng(static_cast<unsigned>(std::time(0)));

        // Shuffle the list of territories using the random number generator
        std::shuffle(allTerritories.begin(), allTerritories.end(), rng);

        // Distribute territories among players in a round-robin fashion
        int currentPlayerIndex = 0;
        for (Territory* territory : allTerritories) {
            players[currentPlayerIndex]->addPlayerTerritories(territory);
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }

        cout << "Territories distributed among players." << endl;

        //shuffle the players randomly
        std::random_device rd;
        // Use the Mersenne Twister random number engine
        std::mt19937 gen(rd());
        
        // Shuffle the players vector using the random number generator
        std::shuffle(players.begin(), players.end(), gen);

        for (Player* player : players) {
            player->setReinforcementPool(50);
            cout << player->getName() << " has been assigned" << player->getReinforcementPool() << "armies." << endl;
        }

        for (Player* player : players) {
            player->getPlayerHand()->draw();
            player->getPlayerHand()->draw();

            cout << player->getName() << " has been drawned 2 cards." << endl;
        }

        gameStarted = true;
    }

    if(c == "win") {
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
    cout << "!~~ WELCOME TO WARZONE ~~!" << endl;
    cout << "--------------------------\n" << endl;
    cout << "This application requires input.\nEnable console commands or read from file? (-command or -file)" << endl;

    string answer = "";
    cin >> answer;

    while(answer != "-command" && answer != "-file") {
        cout << "Invalid command, please enter one of '-command' or '-file': ";
        cin >> answer; 
    }

    
    if(answer == "-command") {
        cout << "Command line selected." << endl;

        this->processor = new CommandProcessor('c');
        this->fileProcessor = NULL;
    }

    else {
        cout << "Enter the filename for your desired file: ";
        cin >> answer;

        this->fileProcessor = new FileCommandProcessorAdapter(answer);
        this->processor = NULL;
    }


    cout << "Game Started.\n--------------" << endl;

    while (true)
    {
        string state = stateToString();
        cout << "You are now in the state: " << stateToString() << "\n";
        if(processor != NULL) processor->setState(state);
        else fileProcessor->setState(state);

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

                cout << "Enter command to trigger state change: ";
                
                if(processor != NULL) {
                    cin >> *processor;
                    
                    if(processor->hasNew()) {
                        if(executeCommand(processor->getCommand()))
                            executeStateChange(processor->getCommand().getEffect());
                        processor->removeNew();
                    }
                }

                else {
                    cin >> *fileProcessor;
                    
                    if(fileProcessor->hasNew()) {
                        
                        if(executeCommand(fileProcessor->getCommand()))
                            executeStateChange(fileProcessor->getCommand().getEffect());
                            
                        fileProcessor->removeNew();
                    }
                }
            }
            else {
                startupPhase();
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
