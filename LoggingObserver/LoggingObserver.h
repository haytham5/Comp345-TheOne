#pragma once
#include<string>
#include<vector>
#include<fstream>
using namespace std;

//Free function
void testLoggingObserver();

//Interface (will be inherited by all classes that can be logged)
class ILoggable{
public:
    //Pure virtual function
    virtual string stringToLog()=0;
};

//Abstract class/interface that receives updates from subjects
class Observer{
public:
    virtual ~Observer();
    Observer(const Observer& other);
    virtual void update(ILoggable* loggable)=0;
    friend ostream& operator<<(ostream& os, const Observer& obj);
    Observer& operator=(const Observer& other);
protected:
    Observer();
};

//Notifies observer of changes and maintains a vector of observers
class Subject{
public:
    Subject();
    Subject(const Subject& other);
    ~Subject();
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notify(ILoggable* loggable);
    Subject& operator=(const Subject& other);
    friend ostream& operator<<(ostream& os, const Subject& subject);
private:
    vector<Observer*> observers;
};

//Class responsible for writing logs to the gamelog.txt file
class LogObserver : public Observer{
public:
    LogObserver();
    LogObserver(Subject* subject);
    LogObserver(const LogObserver& other);
    ~LogObserver();
    void update(ILoggable* loggable) override;
    LogObserver& operator=(const LogObserver& other);
    friend ostream& operator<<(ostream& os, const LogObserver& logObserver);
private:
    ofstream logFile;
    string logFileName;
    Subject* subject;
};