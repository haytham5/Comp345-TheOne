#include <iostream>
#include "Player/Player.h"
#include "Orders/Order.h"
#include "Card/Card.h"
#include "GameEngine/GameEngine.h"
#include "Map/Map.h"
#include <iostream>
#include <string>

using namespace std;

int main() {    
    // string s = "";
    // cout << "======= TEST CARDS =======" << endl;
    // testCards();

    // cout << "End Test. type 'next' and Enter to continue to MAPS:";
    // cin >> s;
    // cout << "\n======= TEST MAPS =======" << endl;
    // testLoadMaps();

    // cout << "End Test. type 'next' and Enter to continue to ORDERS:";
    // cin >> s;
    // cout << "\n======= TEST ORDERS =======" << endl;
    // testOrdersList();

    // cout << "End Test. type 'next' and Enter to continue to PLAYERS:";
    // cin >> s;
    // cout << "\n======= TEST PLAYERS =======" << endl;
    // testPlayers();

    // cout << "End Test. type 'next' and Enter to continue to ENGINE:";
    // cin >> s;
    // cout << "\n======= TEST ENGINE =======" << endl;
    // testGameEngine();

    string s = "";
    cout << "======= TEST COMMAND PROCESSOR =======" << endl;
    testCommandProcessor();

    cout << "End Test. type 'next' and Enter to continue to STARTUP PHASE:";
    cin >> s;
    cout << "\n======= TEST STARTUP PHASE =======" << endl;
    testStartupPhase();

    cout << "End Test. type 'next' and Enter to continue to MAIN GAMELOOP:";
    cin >> s;
    cout << "\n======= TEST MAIN GAMELOOP =======" << endl;
    testMainGameLoop();

    cout << "End Test. type 'next' and Enter to continue to ORDER EXECUTION:";
    cin >> s;
    cout << "\n======= TEST ORDER EXECUTION =======" << endl;
    testOrderExecution();

    cout << "End Test. type 'next' and Enter to continue to OBSERVER:";
    cin >> s;
    cout << "\n======= TEST OBSERVER =======" << endl;
    testLoggingObserver();

    return 0;
}