#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <random>
#include "GameEngine.h"
#include "../Player/Player.h"
#include "../CommandProcessing/CommandProcessing.h"

using namespace std;

typedef GameEngine::GameState GS;

// default constructor
GameEngine::GameEngine()
{
    this->state = START;

    this->gameStarted = false;

    this->mapLoader = new MapLoader();

    this->tournamentMode = false;
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
        string state = stateToString();
        cout << "You are now in the state: " << stateToString() << "\n";
        if (processor != NULL)
            processor->setState(state);
        else
            fileProcessor->setState(state);

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
    // Notifies observers
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

// function to covert string to enum
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
        Deck *d = new Deck();
        Map *m = new Map();

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
                players.push_back(new Player(playerName, m, new Hand(d), new OrdersList()));
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
            cout << player->getName() << " has been assigned " << player->getReinforcementPool() << " armies." << endl;
        }

        for (Player *player : players)
        {
            player->draw();
            player->draw();

            cout << player->getName() << " has been drawned 2 cards." << endl;
        }

        gameStarted = true;
    }

    if (c == "quit" || c == "replay")
    {
        gameStarted = false;
    }

    return true;
}

GameEngine &GameEngine::operator=(GameEngine &gameEngine)
{
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
    string state = "";
    cout << "!~~ WELCOME TO WARZONE ~~!" << endl;

    cout << "Would you like to enable tournament mode? YES or NO\n"
         << endl;

    string tournamentModeAnswer = "";
    cin >> tournamentModeAnswer;
    if (tournamentModeAnswer == "YES")
    {
        tournamentMode = true;
        string command;
        cout << "Game is now in tournament mode \n";
        cout << "Enter the tournament mode command in the format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>";
        cin >> command;
        processor->processTournamentCommand(command);
        validateTournament();
    }
    /*
    if (tournamentMode == "-tournament")
    {
        cout << "Tournament mode enabled." << endl;
        cout << "Enter the number of maps you would like to play on: ";
        int maps = 0;
        cin >> maps;
        while (maps < 1 || maps > 5)
        {
            cout << "Invalid number of maps, please enter a number between 1 and 5: ";
            cin >> maps;
        }

        cout << "Enter the number of players you would like to play with: ";
        int players = 0;
        cin >> players;
        while (players < 2 || players > 4)
        {
            cout << "Invalid number of players, please enter a number between 2 and 4: ";
            cin >> players;
        }

        cout << "Enter the number of games you would like to play per map: ";
        int games = 0;
        cin >> games;
        while (games < 1 || games > 5)
        {
            cout << "Invalid number of games, please enter a number between 1 and 5: ";
            cin >> games;
        }

        cout << "Enter the number of turns you would like to play per game: ";
        int turns = 0;
        cin >> turns;
        while (turns < 10 || turns > 50)
        {
            cout << "Invalid number of turns, please enter a number between 10 and 50: ";
            cin >> turns;
        }

        runTournament(maps, players, games, turns);
        return;
    }
    */

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

    while (state != "END")
    {
        state = stateToString();
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
            if (gameStarted && !startupTest)
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

            else if (state != "END" && state != "WIN")
            {
                startupPhase();
            }

            if (gameStarted && startupTest)
            {
                break;
            }
        }
    }
    cout << "Game Over" << endl;
}

void testGameEngine()
{
    GameEngine *engine = new GameEngine();

    engine->run();
}

void testStartupPhase()
{
    GameEngine *engine = new GameEngine();

    engine->startupTest = true;

    engine->run();
}

// For game log
string GameEngine::stringToLog()
{
    return "Game State is now: " + stateToString();
}

// round robin fashion cycle through 3 phases -> reinforcement, issue orders and execute orders
void GameEngine::mainGameLoop(bool test = false)
{
    int turns = processor->getTournamentMaxNumberOfTurns();

    if (tournamentMode = false)
    {
        while (players.size() != 1)
        {
            cout << "Players in the game:  ";
            // if player territories list size is 0, they are removed from game
            vector<int> deleteIndexes;

            for (int i = 0; i < players.size(); i++)
            {
                if (players[i]->getPlayerTerritories().empty())
                {
                    players[i]->setName(players[i]->getName() + " - Empty Territories, will be removed from the game");
                    deleteIndexes.push_back(i);
                }

                cout << players[i]->getName();
                if (i == players.size() - 1)
                    cout << "." << endl;
                else
                    cout << ", ";
            }

            for (auto it : deleteIndexes)
                players.erase(players.begin() + it);

            reinforcementPhase();
            issueOrdersPhase();
            executeOrdersPhase();

            if (test)
                break;
        }
    }
    else
    {
        while (turns != 0)
        {
            cout << "Players in the game:  ";
            // if player territories list size is 0, they are removed from game
            vector<int> deleteIndexes;

            for (int i = 0; i < players.size(); i++)
            {
                if (players[i]->getPlayerTerritories().empty())
                {
                    players[i]->setName(players[i]->getName() + " - Empty Territories, will be removed from the game");
                    deleteIndexes.push_back(i);
                }

                cout << players[i]->getName();
                if (i == players.size() - 1)
                    cout << "." << endl;
                else
                    cout << ", ";
            }

            for (auto it : deleteIndexes)
                players.erase(players.begin() + it);

            reinforcementPhase();
            issueOrdersPhase();
            executeOrdersPhase();

            if (test)
                break;

            turns--;
        }
    }
}

void GameEngine::reinforcementPhase()
{

    for (int i = 0; i < players.size(); i++)
    {
        cout << "Player: " << players[i]->getName() << "'s updated reinforcement pool:" << endl;
        // if the number of territories owned / 3 is less than 3, number of reinforcement army units for the player is 3
        if (((players[i]->getPlayerTerritories().size()) / 3) < 3)
        {
            players[i]->setReinforcementPool(3);
            cout << "Player: " << players[i]->getName() << " has a reinforcement pool of " << players[i]->getReinforcementPool() << endl;
        }
        // else if the player owns all the territories of an entire continent, the player is given a number of army units corresponding to the continent’s control bonus value
        else if (players[i]->ownAllTerritoryInContinent())
        {
            players[i]->setReinforcementPool(10);
            cout << "Player: " << players[i]->getName() << " has a reinforcement pool of " << players[i]->getReinforcementPool() << endl;
        }
        else
        {
            int mod = ((players[i]->getPlayerTerritories().size()) / 3);
            players[i]->setReinforcementPool(mod);
            cout << "Player: " << players[i]->getName() << " has a reinforcement pool of" << players[i]->getReinforcementPool() << endl;
        }
    }
}

// each player adds orders to their order list
void GameEngine::issueOrdersPhase()
{
    string order;
    string answer;

    // If game is in tournament mode, there is no user interaction and the orders are just issued based on the player's cards
    if (tournamentMode = false)
    {
        for (int i = 0; i < players.size(); i++)
        {
            string name = players[i]->getName();
            vector<Card *> currentPlayerCards = players[i]->getPlayerHand()->getCards();

            while (answer != "NO")
            {
                cout << "Player: " << name << " your cards are: \n";
                for (int j = 0; j < currentPlayerCards.size(); j++)
                {
                    cout << "Card " << (j + 1) << ": " << currentPlayerCards.at(j)->getType() << endl;
                }
                cout << "Player: " << name << " input your order here: ";
                cin >> order;
                while (order != "")
                {
                    if (order == "Advance" || order == "Deploy" || order == "Bomb" || order == "Blockade" || order == "Airlift" || order == "Negotiate")
                    {
                        for (int k = 0; k < currentPlayerCards.size(); k++)
                        {
                            if (order == currentPlayerCards.at(k)->getType())
                            {
                                players[i]->issueOrder(order);
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid Order! Try Again: ";
                        cin >> order;
                    }

                    break;
                }

                cout << "Would you like to issue another order? YES or NO: " << endl;
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
    else
    {
        for (int i = 0; i < players.size(); i++)
        {
            string name = players[i]->getName();
            vector<Card *> currentPlayerCards = players[i]->getPlayerHand()->getCards();
            for (int j = 0; j < currentPlayerCards.size(); j++)
            {
                string order = currentPlayerCards.at(j)->getType();
                players[i]->issueOrder(order);
            }
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
            Order *order = players[i]->getOrderList()->getOrderAt(j);
            if (order->baseType == "Deploy")
            {
                cout << "Player: " << players[i]->getName() << " executes deploy orders...";
                order->execute();
            }
        }
    }

    // game engine proceeds to execute the top order on the list of orders of each player in a round-robin fashion
    for (int i = 0; i < players.size(); i++)
    {
        OrdersList *playerOrderList = players[i]->getOrderList();

        Order *order = playerOrderList->getOrderAt(i);
        if (order->baseType != "Deploy")
        {
            cout << "Player: " << players[i]->getName() << " executes order:\n"
                 << order->getDescription();

            if (order->getDescription() != "")
                order->execute();
            else
                cout << "Error occured." << endl;
        }
    }
}

void GameEngine::runGame(int map, int players, int turns)
{
    // Add game logic here
}

void GameEngine::validateTournament()
{
    int numOfGames = processor->getTournamentNumberOfGames();
    int numOfTurns = processor->getTournamentMaxNumberOfTurns();
    vector<string> listOfMaps = processor->getTournamentListOfMapFiles();
    vector<string> listOfPlayerStrategies = processor->getTournamentListOfPlayerStrategies();

    if (listOfMaps.size() < 1 || listOfMaps.size() > 5)
    {
        cout << "GameEngine::validateTournament:: Error | Number of maps must be between 1 and 5";
        exit(0);
    }
    if (listOfPlayerStrategies.size() < 2 || listOfPlayerStrategies.size() > 4)
    {
        cout << "GameEngine::validateTournament:: Error | Number of players must be between 2 and 4";
        exit(0);
    }
    if (numOfGames < 1 || numOfGames > 5)
    {
        cout << "GameEngine::validateTournament:: Error | Number of games must be between 1 and 5";
        exit(0);
    }
    if (numOfTurns < 10 || numOfGames > 50)
    {
        cout << "GameEngine::validateTournament:: Error | Number of turns must be between 10 and 50";
        exit(0);
    }

    runTournament(listOfMaps, listOfPlayerStrategies, numOfGames, numOfTurns);
}

void GameEngine::runTournament(vector<string> maps, vector<string> playerStrategies, int games, int turns)
{
    std::ofstream logFile("tournament_log.txt");

    if (!logFile.is_open())
    {
        std::cerr << "Error opening log file." << std::endl;
        return;
    }

    logFile << "Tournament started with " << maps.size() << " maps, " << players.size() << " players, "
            << games << " games per map, and " << turns << " turns per game." << std::endl;

    for (int i = 0; i < players.size(); i++)
    {
        // TODO add logic to create a player with specific strategy and add to players
    }

    // Run the tournament
    for (int map = 1; map < maps.size(); map++)
    {
        mapLoader->loadMapFromFile(maps[map]);
        for (int game = 1; game <= games; ++game)
        {
            mainGameLoop();
            //  Winner is player with most territories
            int maxTerritories = 0;
            string winner;
            for (int i = 0; i < players.size(); i++)
            {
                vector<Territory *> playerTerritories = players[i]->getPlayerTerritories();
                if (playerTerritories.size() >= maxTerritories)
                {
                    maxTerritories = playerTerritories.size();
                    winner = players[i]->getName();
                }
            }
            logFile << "Map " << map << ", Game " << game << ": " << winner << std::endl;
        }
    }

    logFile << "Tournament completed." << std::endl;
    logFile.close();
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

    engine->mainGameLoop(true);
}

void GameEngine::testTournamentMode()
{
    cout << "Would you like to enable tournament mode? YES or NO\n"
         << endl;

    string tournamentModeAnswer = "";
    cin >> tournamentModeAnswer;
    if (tournamentModeAnswer == "YES")
    {
        tournamentMode = true;
        string command;
        cout << "Game is now in tournament mode \n";
        cout << "Enter the tournament mode command in the format: tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>";
        cin >> command;
        processor->processTournamentCommand(command);
        validateTournament();
    }
}