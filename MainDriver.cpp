#include <iostream>
#include "Player/Player.h"
#include "Orders/Order.h"
#include "Card/Card.h"
#include "GameEngine\GameEngine.h" 
#include "Map/Map.h"
#include <iostream>
#include <string>

using namespace std;

int main() {    
    string s = "";
    cout << "======= TEST CARDS =======" << endl;
    testCards();

    cout << "End Test. type 'next' and Enter to continue to MAPS:";
    cin >> s;
    cout << "\n======= TEST MAPS =======" << endl;
    testLoadMaps();

    cout << "End Test. type 'next' and Enter to continue to ORDERS:";
    cin >> s;
    cout << "\n======= TEST ORDERS =======" << endl;
    testOrdersList();

    cout << "End Test. type 'next' and Enter to continue to PLAYERS:";
    cin >> s;
    cout << "\n======= TEST PLAYERS =======" << endl;
    testPlayers();

    cout << "End Test. type 'next' and Enter to continue to ENGINE:";
    cin >> s;
    cout << "\n======= TEST ENGINE =======" << endl;
    testGameEngine();

    return 0;
}