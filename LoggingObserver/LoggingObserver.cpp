#include "LoggingObserver.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Orders/Order.h"
#include "../Map/Map.h"
#include<iostream>
using namespace std;

//Default constructor
Subject::Subject(){
    //No need for anything here since "observers" vector is empty by default
}

//Copy constructor
Subject::Subject(const Subject &other){
    this->observers=other.observers;
}

//Destructor
Subject::~Subject(){
    for(auto elem : observers){
        delete elem;
    }
}

//Adds a given observer pointer into the observers vector
void Subject::attach(Observer *observer){
    observers.push_back(observer);
}

//Deletes a given observer in the observers vector
void Subject::detach(Observer *observer){
    int eraseIndex = -1;
    //Finds the observer in the observers vector and remove it
    for(int i = 0; i < observers.size(); i++) {
        if(observers.at(i) == observer) {eraseIndex = i;break;}
    }
    
    if(eraseIndex != -1) observers.erase(observers.begin() + eraseIndex);
}

//Allows subjects to notify observers of the necessary events
void Subject::notify(ILoggable *loggable){
     cout<< "\nNotifying..."<<endl;
    for(auto elem : observers){
        elem->update(loggable);
    }
}

//Assignment operator for Subject class
Subject &Subject::operator=(const Subject &other){
    if(this != &other) {
        //Clean up current observers
        for(auto elem : observers){
            delete elem;
        }
        //Copy the observers from the other object
        observers= other.observers;
    }
    return *this;
}

//Stream insertion operator for Subject class
ostream &operator<<(ostream &os, const Subject &subject){
    os<< "Subject with Observers:\n";
    for(auto elem : subject.observers){
         os << " - " << *elem << "\n";
    }
    return os;
}

//Assignmnet operator for Observer class
Observer &Observer::operator=(const Observer &other){
    return *this;
}

//Default constructor
Observer::Observer(){
    //Nothing needed here
}

//Destructor
Observer::~Observer(){
    //Nothing needed here
}

Observer::Observer(const Observer &other){
    //No addditional logic needed here
}

//Stream insertion operator for Observer class
ostream &operator<<(ostream &os, const Observer &obj){
    os << "Observer";
    return os;
}

//Default constructor
LogObserver::LogObserver(){
    //Nothing needed here
}

//Paramaterized constructor that opens file with given fileName and attaches the subject
LogObserver::LogObserver(Subject* subject){
this->logFileName="gamelog.txt";
this->subject=subject;
 try{   
    logFile.open(logFileName);
    if (!logFile.is_open()) {
            throw runtime_error("Error: Unable to open the file in the paramaterized constructor");
        }

    //Attach this observer to the subject if the subject is not nullptr
    if(subject){
        subject->attach(this);
    }
    else{
        cout<<"Cannot attach subject since it is nullptr"<<endl;
    }
 }
 catch(const exception& e){
    cerr<<"Error: Unable to open file with name: "<<logFileName<<"in parameterized constructor"<<endl;
    cerr<<e.what()<<endl;
 }
}

//Copy constructor
LogObserver::LogObserver(const LogObserver &other){
    logFileName = other.logFileName;

    //Ensuring the log file is closed for the new instance
    if (logFile.is_open()) {
        logFile.close();
    }

    //Open the log file for the new instance
    logFile.open(logFileName);

    //Copy the subject and attach this observer to the new subject
    subject = other.subject;
    if(subject){
        subject->attach(this);
    }
}

//Destructor that closes the file
LogObserver::~LogObserver(){
cout<< "LogObserver Destructor called"<<endl;
try{  
 //Detach this observer from the subject if the subject is not nullptr
 if (subject){
     subject->detach(this);
    } 

 if (logFile.is_open()){
        logFile.close();
    }
 }
 catch(const exception& e){
    cerr<<"Error: Unable to close file in destructor"<<endl;
    cerr<<e.what()<<endl;
 }  
}

//Overriding and implementing the pure virtual update method. It writes to the log file.
void LogObserver::update(ILoggable *loggable){
    cout<<"Updating..."<<endl;
    if(logFile.is_open()){
        logFile<< loggable->stringToLog()<<endl;
    }
    else{
        cout<<"Log file is not opened. Cannot call update on it."<<endl;
    }
}

//Assignment operator for LogObserver class
LogObserver &LogObserver::operator=(const LogObserver &other){
    if(this!= &other) {
        //Close the current log file if open
        if(logFile.is_open()){
            logFile.close();
        }

        //Copy logFileName from the other object
        logFileName= other.logFileName;

        //Open the log file for the new instance
        logFile.open(logFileName);

        //Copy the subject and attach this observer to the new subject (if it is not nullptr)
        subject= other.subject;
        if(subject){
            subject->attach(this);
        }
    }
    return *this;
}

//Stream insertion operator for LogObserver class
ostream &operator<<(ostream &os, const LogObserver &logObserver){
    os<<"LogObserver: logFileName:"<< logObserver.logFileName;
    if(logObserver.subject){
        os<< ", attached to: "<< *logObserver.subject;
    }
    return os;
}

//Free function
void testLoggingObserver(){

    cout<< "Testing LogObserver:"<<endl;

    //Instantiating  Territories (will be used by the orders)
    Territory* terr= new Territory("Canada",0,1,"North America");
    Territory* terr2= new Territory("America",0,2,"North America");

    //Instantiating concrete subjects
    Command* cmd= new Command();
    CommandProcessor* cmdP= new CommandProcessor();
    GameEngine* game = new GameEngine();
    OrdersList* oList= new OrdersList();
    BlockadeOrder* blockOrder= new BlockadeOrder(terr, "Player 1");

    //Instantiating concrete observer
    LogObserver* logO = new LogObserver(cmd);

    //Attaching observers to subjects
    cmdP->attach(logO);
    game->attach(logO);
    oList->attach(logO);
    blockOrder->attach(logO);

    //Testing that gamelog successfully writes the information for CommandProcessing and Command class
    cmdP->testSaveCommand("blue","red");
    cmd->saveEffect("testEffect");

    //Testing that gamelog successfully writes the information for GameEngine class
    game->executeStateChange("MAP_LOADED");
    game->executeStateChange("GAME_START");

    //Testing that gamelog successfully writes the information for Order and OrdersList class
    oList->addOrder(blockOrder);
    //Will not be printed since execute() will fail validation and thus will not be executed
    blockOrder->execute();

    cout<<"Done testing, check gamelog.txt"<<endl;

}
