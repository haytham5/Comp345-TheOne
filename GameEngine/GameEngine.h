#include <iostream>
#include <string>
#include <vector>
#include "../CommandProcessing/CommandProcessing.h"
#include "../Player/Player.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Map/Map.h"

using namespace std;

class GameEngine : public ILoggable, public Subject
{
public:
    // different states the game can be in
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
    // default constructor
    GameEngine();

    // copy constructor
    GameEngine(GameEngine &gameEngine);

    // Run
    void run();

    // function to get current state of game
    GameState getGameState();

    void startupPhase();

    // Transition states
    void transition(GameEngine::GameState);

    // function to convert states to string
    std::string stateToString();

    // Function to convert string to state
    GameState stringToState(string s);

    // Executes command, if command needs to be executed
    bool executeCommand(Command command);

    // Changes state
    void executeStateChange(string stateChange);

    // Method that returns a vector of current players
    vector<Player *> getPlayers();

    // Method that sets the current players
    void setPlayers(vector<Player *> p);

    // Main game loop to cycle through the Reinforcement, Issue Orders and Order Execution Phases
    void mainGameLoop(bool t);

    // Reinforcement Phase
    void reinforcementPhase();

    // Issuing Orders Phase
    void issueOrdersPhase();

    // Orders Execution Phase
    void executeOrdersPhase();

    // Run a Single Game
    void runGame(int map, int players, int turns);

    // Validate the tournament parameters
    void validateTournament();

    // Run Tournament
    void runTournament(vector<string> maps, vector<string> playerStrategies, int games, int turns);

    GameEngine &operator=(GameEngine &gameEngine);

    friend ostream &operator<<(ostream &os, GameEngine &gameEngine);

    friend ostream &operator<<(ostream &os, GameEngine &gameEngine);

    virtual string stringToLog() override;

    bool startupTest = false;

private:
    // Game started
    bool gameStarted;

    // state of the game
    GameState state;

    // Processor
    CommandProcessor *processor;

    FileCommandProcessorAdapter *fileProcessor;

    vector<Player *> players;
    int currentPlayerIndex;

    MapLoader *mapLoader;

    string currentMap;

    Map map;

    bool tournamentMode;
};

// test for game engine in part 5 of assignment 1
void testGameEngine();

void testStartupPhase();

// test for main game loop in part 3 of assignment 2
void testMainGameLoop();
