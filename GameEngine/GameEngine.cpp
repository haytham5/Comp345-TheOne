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
#include "../Player/Player.h"
#include "../CommandProcessing/CommandProcessing.h"

typedef GameEngine::GameState GS;

// default constructor
GameEngine::GameEngine()
{
    this->state = START;

    this->gameStarted = false;

    this->mapLoader = new MapLoader();
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

void GameEngine::startupPhase()
{
    std::cout << "Startup Phase\n";
    while (!this->gameStarted)
    {
        cout << "Enter command to trigger state change: ";
        if (processor != NULL)
        {
            cin >> *processor;

            if (processor->hasNew())
            {
                if (executeCommand(processor->getCommand()))
                    executeStateChange(processor->getCommand().getEffect());
                processor->removeNew();
            }
        }

        else
        {
            cin >> *fileProcessor;

            if (fileProcessor->hasNew())
            {

                if (executeCommand(fileProcessor->getCommand()))
                    executeStateChange(fileProcessor->getCommand().getEffect());

                fileProcessor->removeNew();
            }
        }
    }
}

// function to transition to next state
void GameEngine::transition(GS state)
{
    this->state = state;
    //Notifies observers
    notify(this);
}

// execute the state change based on which state the game is currrently in
void GameEngine::executeStateChange(string stateChange)
{
    GS state = stringToState(stateChange);

    transition(state);
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
        END};

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
        "END"};

    for (int i = 0; i < sizeof(stringArray); i++)
        if (stringArray[i] == s)
            return gsArray[i];

    return END;
}

vector<Player *> GameEngine::getPlayers()
{
    return players;
}

void GameEngine::setPlayers(vector<Player *> p)
{
    players = p;
}

bool GameEngine::executeCommand(Command command)
{
    string c = command.getCommand();
    string e = command.getEffect();

    // TODO: ENGINE ACTIONS BASED ON STATE (PART 2)
    // IF LOADMAP, ASK FOR MAP FILENAME

    // IF VALIDATEMAP, VALIDATE MAP

    // IF ADDPLAYER, ASK FOR PLAYER NAMES, ETC...

    // RETURN FALSE IF THERE IS PROBLEM EXECUTING COMMAND

    if (c == "loadmap")
    {
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

    if (c == "validatemap")
    {
        // if(mapLoader->isValidMapFile(currentMap)){
        //     cout << currentMap << " is valid." << endl;
        // }
        // else{
        //     cout << currentMap << " is invalid." << endl;
        // }
    }

    if (c == "addplayer")
    {
        if (currentPlayerIndex != 5)
        {
            string playerName;
            cout << "Enter the player name: ";
            cin >> playerName;

            // Check if the player name already exists
            bool nameExists = false;
            for (const auto &player : players)
            {
                if (player->getName() == playerName)
                {
                    nameExists = true;
                    break;
                }
            }

            if (!nameExists)
            {
                players.push_back(new Player(playerName, nullptr, nullptr, nullptr));
                currentPlayerIndex++;
                cout << "Player " << playerName << " added." << endl;
            }
            else
            {
                cout << "Player with the name " << playerName << " already exists." << endl;
            }
        }
        else
        {
            cout << "Max number of players reached." << endl;
        }
    }

    if (c == "gamestart")
    {
        // Get the list of territories from the map
        vector<Territory *> allTerritories = map.getTerritories();

        // Seed for random number generation
        std::default_random_engine rng(static_cast<unsigned>(std::time(0)));

        // Shuffle the list of territories using the random number generator
        std::shuffle(allTerritories.begin(), allTerritories.end(), rng);

        // Distribute territories among players in a round-robin fashion
        int currentPlayerIndex = 0;
        for (Territory *territory : allTerritories)
        {
            players[currentPlayerIndex]->addPlayerTerritories(territory);
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }

        cout << "Territories distributed among players." << endl;

        // shuffle the players randomly
        std::random_device rd;
        // Use the Mersenne Twister random number engine
        std::mt19937 gen(rd());

        // Shuffle the players vector using the random number generator
        std::shuffle(players.begin(), players.end(), gen);

        for (Player *player : players)
        {
            player->setReinforcementPool(50);
            cout << player->getName() << " has been assigned" << player->getReinforcementPool() << "armies." << endl;
        }

        for (Player *player : players)
        {
            player->getPlayerHand()->draw();
            player->getPlayerHand()->draw();

            cout << player->getName() << " has been drawned 2 cards." << endl;
        }

        gameStarted = true;
    }

    if (c == "win")
    {
        gameStarted = false;
    }

    return true;
}

GameEngine& GameEngine::operator=(GameEngine& gameEngine) {
  this->state = gameEngine.getGameState();
  return *this;
}

ostream &operator<<(ostream &os, GameEngine &gameEngine)
{
    os << "Current Game State: " << gameEngine.stateToString() << endl;
    return os;
}

void GameEngine::run()
{
    cout << "!~~ WELCOME TO WARZONE ~~!" << endl;
    cout << "--------------------------\n"
         << endl;
    cout << "This application requires input.\nEnable console commands or read from file? (-command or -file)" << endl;

    string answer = "";
    cin >> answer;

    while (answer != "-command" && answer != "-file")
    {
        cout << "Invalid command, please enter one of '-command' or '-file': ";
        cin >> answer;
    }

    if (answer == "-command")
    {
        cout << "Command line selected." << endl;

        this->processor = new CommandProcessor('c');
        this->fileProcessor = NULL;
    }

    else
    {
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
        if (processor != NULL)
            processor->setState(state);
        else
            fileProcessor->setState(state);

        if (state == "END")
        {
            break;
        }
        else
        {
            if (gameStarted)
            {
                // MAIN GAMEPLAYLOOP (PART 3)
                // Run through Players collection and call each playerprocessor
                // EXAMPLE:
                //  cout << "Player 1, enter your command: ";

                cout << "Enter command to trigger state change: ";

                if (processor != NULL)
                {
                    cin >> *processor;

                    if (processor->hasNew())
                    {
                        if (executeCommand(processor->getCommand()))
                            executeStateChange(processor->getCommand().getEffect());
                        processor->removeNew();
                    }
                }

                else
                {
                    cin >> *fileProcessor;

                    if (fileProcessor->hasNew())
                    {

                        if (executeCommand(fileProcessor->getCommand()))
                            executeStateChange(fileProcessor->getCommand().getEffect());

                        fileProcessor->removeNew();
                    }
                }
            }
            else
            {
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

//For game log
string GameEngine::stringToLog()
{
    return "Game State is now: "+stateToString();
}

// round robin fashion cycle through 3 phases -> reinforcement, issue orders and execute orders
void GameEngine::mainGameLoop()
{

    while (players.size() != 1)
    {
        cout << "Players in the game:  ";
        // if player territories list size is 0, they are removed from game
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getPlayerTerritories().empty())
            {
                delete players[i];
            }
            cout << players[i]->getName() << ", ";
        }

        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
    }
}

void GameEngine::reinforcementPhase()
{

    for (int i = 0; i < players.size(); i++)
    {
        cout << "Player: " << players[i]->getName() << "'s updated reinforcement pool:";
        // if the number of territories owned / 3 is less than 3, number of reinforcement army units for the player is 3
        if (((players[i]->getPlayerTerritories().size()) / 3) < 3)
        {
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 3);
            cout << "Player: " << players[i]->getName() << " has a reinforcement pool of" << players[i]->getReinforcementPool();
        }
        // else if the player owns all the territories of an entire continent, the player is given a number of army units corresponding to the continent’s control bonus value
        else if (players[i]->ownAllTerritoryInContinent())
        {
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + 10);
            cout << "Player: " << players[i]->getName() << " has a reinforcement pool of" << players[i]->getReinforcementPool();
        }
        else
        {
            players[i]->setReinforcementPool(players[i]->getReinforcementPool() + ((players[i]->getPlayerTerritories().size()) / 3));
            cout << "Player: " << players[i]->getName() << " has a reinforcement pool of" << players[i]->getReinforcementPool();
        }
    }
}

// each player adds orders to their order list
void GameEngine::issueOrdersPhase()
{
    for (int i = 0; i < players.size(); i++)
    {
        string order;
        string answer;
        string name = players[i]->getName();
        vector<Card *> currentPlayerCards = players[i]->getPlayerHand()->HandCards;

        while (answer != "NO")
        {
            cout << "Player: " << name << " your cards are: \n";
            for (int j = 0; j < currentPlayerCards.size(); j++)
            {
                cout << "Card " << (j + 1) << ": " << currentPlayerCards[j]->getType();
            }
            cout << "Player: " << name << " input your order here: ";
            cin >> order;
            while (order != "")
            {
                if (order == "Advance" || order == "Deploy" || order == "Bomb" || order == "Blockade" || order == "Airlift" || order == "Negotiate")
                {
                    for (int j = 0; j < currentPlayerCards.size(); j++)
                    {
                        if (order == currentPlayerCards[j]->getType())
                        {
                            players[i]->issueOrder(order);
                        }
                        else
                        {
                            cout << "Invalid Order! Try Again";
                            cin >> order;
                        }
                    }
                }
                else
                {
                    cout << "Invalid Order! Try Again" << endl;
                    cin >> order;
                }
            }

            cout << "Would you like to issue another order? YES or NO" << endl;
            cin >> answer;
            if (answer == "NO")
            {
                break;
            }
            cout << "\n"
                 << endl;
        }
    }
}

// Executes the orders for each player
void GameEngine::executeOrdersPhase()
{

    // game engine should execute all deploy orders before any other orders
    for (int i = 0; i < players.size(); i++)
    {
        OrdersList *playerOrderList = players[i]->getOrderList();

        for (int j = 0; j < playerOrderList->getOrdersListSize(); j++)
        {
            Order *order = playerOrderList->getOrders().at(j);
            if (order->getDescription() == "Deploy")
            {
                cout << "Player: " << players[i]->getName() << " executes deploy orders";
                order->execute();
            }
        }
    }

    // game engine proceeds to execute the top order on the list of orders of each player in a round-robin fashion
    for (int i = 0; i < players.size(); i++)
    {
        OrdersList *playerOrderList = players[i]->getOrderList();

        Order *order = playerOrderList->getOrders().at(0);
        cout << "Player: " << players[i]->getName() << " executes order: " << order->getDescription();
        order->execute();
    }
}

void testMainGameLoop()
{
    GameEngine *engine = new GameEngine();

    string name1 = "Player 1";
    string name2 = "Player 2";
    string name3 = "Player 3";
    Map *map = new Map();
    Deck *deck = new Deck();
    Hand *hand = new Hand(deck);
    Hand *hand2 = new Hand(deck);
    Hand *hand3 = new Hand(deck);
    OrdersList *player1OrderList = new OrdersList();
    OrdersList *player2OrderList = new OrdersList();
    OrdersList *player3OrderList = new OrdersList();

    Player player1(name1, map, hand, player1OrderList);
    Player player2(name2, map, hand2, player2OrderList);
    Player player3(name3, map, hand3, player3OrderList);

    vector<Player *> p;
    p.push_back(&player1);
    p.push_back(&player2);
    p.push_back(&player3);
    engine->setPlayers(p);

    // Adding territories to map
    map->addTerritory("TerritoryA", 0, 0, "Continent1");
    map->addTerritory("TerritoryB", 1, 0, "Continent1");
    map->addTerritory("TerritoryC", 2, 0, "Continent2");
    map->addTerritory("TerritoryD", 3, 0, "Continent2");

    // Adding edges
    map->addEdge("TerritoryC", "TerritoryB");

    // Assigning territories to players
    player1.addPlayerTerritories(map->getTerritory("TerritoryA"));
    player1.addPlayerTerritories(map->getTerritory("TerritoryB"));
    player2.addPlayerTerritories(map->getTerritory("TerritoryC"));
    player2.addPlayerTerritories(map->getTerritory("TerritoryD"));

    engine->mainGameLoop();
}
