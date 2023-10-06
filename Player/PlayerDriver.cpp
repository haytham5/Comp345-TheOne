#include "Player.h"

using namespace std;

//Free function
void testPlayers(){
    
    string name1="Player 1";
    string name2="Player 2";
    Map* map= new Map();
    Deck* deck=new Deck();
    Hand* hand=new Hand(deck);
    Hand* hand2=new Hand(deck);
    OrdersList* player1OrderList= new OrdersList();
    OrdersList* player2OrderList= new OrdersList();

    Player player1(name1,map,hand, player1OrderList);
    Player player2(name2,map,hand2, player2OrderList);
    
    //Adding territories to map
    map->addTerritory("TerritoryA", 0, 0, "Continent1");
    map->addTerritory("TerritoryB", 1, 0, "Continent1");
    map->addTerritory("TerritoryC", 2, 0, "Continent2");
    map->addTerritory("TerritoryD", 3, 0, "Continent2");

    //Adding edges
    map->addEdge("TerritoryC","TerritoryB");

    //Assigning territories to players 
    player1.addPlayerTerritories(map->getTerritory("TerritoryA"));
    player1.addPlayerTerritories(map->getTerritory("TerritoryB"));
    player2.addPlayerTerritories(map->getTerritory("TerritoryC"));
    player2.addPlayerTerritories(map->getTerritory("TerritoryD"));


    //Printing out Players' names
    cout<< "\nPlayer 1 Name: "<<player1.getName()<<endl;
    cout<< "\nPlayer 2 Name: "<<player2.getName()<<endl;

    //Printing out Player 1's territories
    cout <<"\nPlayer 1's Territories:"<< endl;
    vector<Territory*> player1Territories= player1.getPlayerTerritories();
    if(player1Territories.empty()){
        cout<<"Player 1 has no territories"<<endl;
    }
    for(Territory* territory: player1Territories) {
        cout<< territory->getName()<< endl;
    }

    //Printing out Player 2's territories
    cout<< "\nPlayer 2's Territories:"<< endl;
    vector<Territory*> player2Territories= player2.getPlayerTerritories();
    if(player2Territories.empty()){
       cout<<"Player 2 has no territories"<<endl;
    }
    for(Territory* territory: player2Territories) {
        cout<<territory->getName()<< endl;
    }

    //Calling toDefend() for player 1
    vector<Territory*> territoriesToDefend= player1.toDefend();

    //Calling toAttack() for player 2
    vector<Territory*> territoriesToAttack= player2.toAttack();

    //Showing results for toDefend and toAttack
    cout<<"\nPlayer 1 territories to defend: "<<endl;
    if(territoriesToDefend.empty()){
            cout<<"No territories to defend"<<endl;
        }
    for(Territory* territory: territoriesToDefend){
        cout<<territory->getName()<<endl;
    }

    cout<<"\nPlayer 2 territories to attack: "<<endl;
     if(territoriesToAttack.empty()){
            cout<<"No territories to attack"<<endl;
        }
    for(Territory* territory: territoriesToAttack){
        cout<<territory->getName()<<endl;
    }

    //Printing player 1's hand
    cout<<"\n"<<player1.getName()<<"'s hand:"<<endl;
    player1.getPlayerHand()->print();
    
    //Printing player 2's hand
    cout<<"\n"<<player2.getName()<<"'s hand:"<<endl;
    player2.getPlayerHand()->print();

    //Calling issue order player 1 and player 2 to add orders to their orderlist
    cout<<"\nPlayer 1 is playing: "<<endl;
    player1.issueOrder(player1.getPlayerHand()->play(0));
     cout<<"\n"<<player1.getName()<<"'s hand:"<<endl;
    player1.getPlayerHand()->print();
    player1.issueOrder(player1.getPlayerHand()->play(1));
    cout<<"\n"<<player1.getName()<<"'s hand:"<<endl;
    player1.getPlayerHand()->print();

    cout<<"\nPlayer 2 is playing: "<<endl;
    player2.issueOrder(player2.getPlayerHand()->play(0));
    cout<<"\n"<<player2.getName()<<"'s hand:"<<endl;
    player2.getPlayerHand()->print();
    player2.issueOrder(player2.getPlayerHand()->play(1));
    cout<<"\n"<<player2.getName()<<"'s hand:"<<endl;
    player2.getPlayerHand()->print();

    //Print out player 1's and 2's orderLists
    cout<<"\nPlayer 1's order list:"<<endl;
    player1.printOrderList();
    cout<<"\nPlayer 2's order list:"<<endl;
    player2.printOrderList();

    cout << endl;
    delete map;
    cout << endl;
    delete deck;
    cout <<endl;
}

//Main method
int main(){
    testPlayers();
    return 0;
}