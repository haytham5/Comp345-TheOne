#include "LoggingObserver.h"
#include<iostream>
using namespace std;

//Dtream insertion operator for ILoggable class
ostream &operator<<(ostream &os, const ILoggable &obj){
    // TODO: insert return statement here***************************
}

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
    //Finds the observer in the observers vector and remove it
    auto it= find(observers.begin(),observers.end(),observer);
    if (it!= observers.end()) {
        observers.erase(it);
    }
}

//Allows subjects to notify observers of the necessary events
void Subject::notify(ILoggable *loggable){
    for(auto elem : observers){
        elem->update(loggable);
    }
}

//Assignment operator for Subject class
Subject &Subject::operator=(const Subject &other){
    // TODO: insert return statement here****************************
}

// Stream insertion operator for Subject class
ostream &operator<<(ostream &os, const Subject &subject){
    for(auto elem : subject.observers){
         os << " - " << *elem << "\n";
    }
    return os;
    //TODO (CHANGE THIS?)**************************************
}

//Default constructor
Observer::Observer(){
    //Nothing needed here
}

//Destructor
Observer::~Observer(){
    //Nothing needed here
}

//Stream insertion operator for Observer class
ostream &operator<<(ostream &os, const Observer &obj){
    // TODO: insert return statement here*************************
}

//Default constructor
LogObserver::LogObserver(){
    //Nothing needed here
}

//Paramaterized constructor that opens file with given fileName
LogObserver::LogObserver(const string &fileName,Subject* subject){
this->logFileName=fileName;
this->subject=subject;
 try{   
    logFile.open(fileName);
    if (!logFile.is_open()) {
            throw runtime_error("Error: Unable to open the file with the provided filename in the paramaterized constructor");
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
    cerr<<"Error: Unable to open file with name: "<<fileName<<"in parameterized constructor"<<endl;
    cerr<<e.what()<<endl;
 }
}

//Copy constructor
LogObserver::LogObserver(const LogObserver &other){
    //TODO*********************************************************
}

//Destructor that closes the file
LogObserver::~LogObserver(){
cout<< "Destructor called"<<endl;
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
    if(logFile.is_open()){
        logFile<< loggable->stringToLog()<<endl;
    }
    else{
        cout<<"Log file is not opened. Cannot call update on it."<<endl;
    }
}

//Assignment operator for LogObserver class
LogObserver &LogObserver::operator=(const LogObserver &other){
    // TODO: insert return statement here
}

//Stream insertion operator for LogObserver class
ostream &operator<<(ostream &os, const LogObserver &logObserver){
    os <<"LogObserver: logFileName="<< logObserver.logFileName; 
    return os;
}
