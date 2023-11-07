#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Player/Player.h"

using namespace std;

const string acceptedConsoleCommands[14][3] = {
    {"loadmap", "START", "MAP_LOADED"},
    {"loadmap", "MAP_LOADED", "MAP_LOADED"},
    {"validatemap", "MAP_LOADED", "MAP_VALIDATED"},
    {"addplayer", "MAP_VALIDATED", "PLAYERS_ADDED"},
    {"addplayer", "PLAYERS_ADDED", "PLAYERS_ADDED"},
    {"gamestart", "PLAYERS_ADDED", "ASSIGN_REINFORCEMENT"},
    {"issueorder", "ASSIGN_REINFORCEMENT", "ISSUE_ORDERS"},
    {"issueorder", "ISSUE_ORDERS", "ISSUE_ORDERS"},
    {"endissueorder", "ISSUE_ORDERS", "EXECUTE_ORDERS"},
    {"execorder", "EXECUTE_ORDERS", "EXECUTE_ORDERS"},
    {"endexecorder", "EXECUTE_ORDERS", "ASSIGN_REINFORCEMENT"}, 
    {"win", "EXECUTE_ORDERS", "WIN"},
    {"replay", "WIN", "START"},
    {"quit", "WIN", "END"}
};

const string acceptedPlayerCommands[7][2] = {
    {"Reinforce", "ASSIGN_REINFORCEMENT"},
    {"Advance", "ISSUE_ORDERS"},
    {"Deploy", "ISSUE_ORDERS"},
    {"Airlift", "ISSUE_ORDERS"},
    {"Bomb", "ISSUE_ORDERS"},
    {"Blockade", "ISSUE_ORDERS"},
    {"Negotiate", "ISSUE_ORDERS"}
};

// FREE FUNCTION

void testCommandProcessor()
{
    cout << "TESTING PLAYER COMMANDS: " << endl;

    Player* p = new Player();
    p->setName("test");

    p->testState("ISSUE_ORDERS");

    p->play();

    cout << "TESTING FILE PROCESSOR AND CONSOLE COMMANDS: " << endl;
    GameEngine *engine = new GameEngine();
    
    engine->run();
}

// COMMAND

Command::Command()
{
    string c = "Empty";
    string e = "None";
    command = c;
    effect = e;
}

Command::Command(string c, string e)
{
    command = c;
    effect = e;
}

Command::~Command()
{
}

Command::Command(const Command &c)
{
    this->command = c.command;
    this->effect = c.effect;
}

Command &Command::operator=(const Command &c)
{
    this->command = c.command;
    this->effect = c.effect;
    return *this;
}

ostream &operator<<(ostream &out, const Command &object)
{
    out << "Command: " << object.command << " -> Effect: " << object.effect << endl;
    return out;
}

void Command::saveEffect(string e)
{
    effect = e;
    //Notifies observer
    notify(this);
}

string Command::getEffect()
{
    return effect;
}

string Command::getCommand()
{
    return command;
}

string Command::stringToLog()
{
    return "Effect: "+ effect+" was just saved.";
}

//CONSOLE COMMAND PROCESSING

CommandProcessor::CommandProcessor()
{
    type = 'c';
    newCommand = false;
}

CommandProcessor::CommandProcessor(char type)
{
    this->type = type;
    newCommand = false;
}

CommandProcessor::~CommandProcessor()
{}

CommandProcessor::CommandProcessor(const CommandProcessor &c)
{
    this->type = c.type;
    this->commands = c.commands;
    this->state = c.state;
    this->newCommand = c.newCommand;
}

CommandProcessor &CommandProcessor::operator=(const CommandProcessor &c)
{
    this->type = c.type;
    this->commands = c.commands;
    this->state = c.state;
    this->newCommand = c.newCommand;

    return *this;
}

Command CommandProcessor::getCommand()
{
    Command c;
    if(!commands.empty()){
        return commands.back();
    }
    else return c;
}

void CommandProcessor::setState(string s)
{
    state = s;
}

bool CommandProcessor::hasNew()
{
    return newCommand;
}

void CommandProcessor::removeNew()
{
    newCommand = false;
}

ostream &operator<<(ostream &out, const CommandProcessor &object)
{
    out << "The command processor is of type " << object.type << "." << endl;
    return out;
}

string CommandProcessor::stringToLog()
{
    if(!commands.empty()) {
        Command lastCommand= commands.back();
        string logString;
        
        logString= "Command: "+ lastCommand.getCommand() + " was just saved.";
        return logString;
    } else {
        cout<< "No commands in the vector to log."<<endl;
        return;
    }
}

istream &operator>>(istream &in, CommandProcessor &cproc)
{
    string s = ""; 
    in >> s;

    cproc.readCommmand(s);

    return in;
}

void CommandProcessor::readCommmand(string s)
{
    cout << "READING COMMAND... " << endl;
    cout << "Passed command: " << s << endl;

    saveCommand(s, validate(s));
}

//VALIDATE COMMANDS
string CommandProcessor::validate(string command)
{
    cout << "VALIDATING COMMAND... " << endl;

    //CONSOLE COMMAND VALIDATION
    if(type == 'c') {
        cout << "Scanning console commands... ";
        for(int i= 0; i < sizeof(acceptedConsoleCommands); i++) {
        //Check if console level command or game level command
            if(acceptedConsoleCommands[i][0] == command) {

                cout << "Correct Console command: " << command << "." << endl;

                if(acceptedConsoleCommands[i][1] == state) {
                    cout << "Correct state " << state << ". Validated." << endl;
                    return acceptedConsoleCommands[i][2];
                }
            }
        }
    }

    //PLAYER COMMAND VALIDATION
    else {
        cout << "Scanning player commands... ";

        for(int i= 0; i < sizeof(acceptedPlayerCommands); i++) {
            if(acceptedPlayerCommands[i][0] == command) {

                cout << "Correct Player command: " << command << "." << endl;

                if(acceptedPlayerCommands[i][1] == state) {
                    cout << "Correct state " << state << ". Validated." << endl;
                    return acceptedPlayerCommands[i][0];
                }
            }
        }
    }

    cout << "Command invalid." << endl;

    return "ERROR: Invalid Command";
}

void CommandProcessor::saveCommand(string command, string effect)
{
    
    if(newCommand) cout << "true" << endl;

    if(effect != "ERROR: Invalid Command") {
        cout << "SAVING COMMAND... " << endl;
        newCommand = true;
    }

    else {
        cout << "SAVING ERROR... " << endl;
    }


    commands.push_back(Command(command, effect));

    cout << "Saved Console command: " << commands.back() << endl;
    //Notifies observers
    notify(this);
}

//FILE COMMAND ADAPTER

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filename)
{
    newCommand = false;
    fileEmptyFlag = false;

    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file " + filename);
    }

    string line;

    while(getline(file, line)) {
        fileCollection.push_back(line);
    }

    file.close();

    // for(auto it : fileCollection) cout << it << endl;

    cout << "Commands successfully saved." << endl;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &c)
{
    this->type = c.type;
    this->commands = c.commands;
    this->state = c.state;
    this->newCommand = c.newCommand;
    this->fileCollection = c.fileCollection;
    this->fileEmptyFlag = c.fileEmptyFlag;
}

FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &c)
{
    this->type = c.type;
    this->commands = c.commands;
    this->state = c.state;
    this->newCommand = c.newCommand;
    this->fileCollection = c.fileCollection;
    this->fileEmptyFlag = c.fileEmptyFlag;

    return *this;
}

ostream &operator<<(ostream &out, const FileCommandProcessorAdapter &object)
{
    out << "File Command Processor Adapter is of type " << object.type << "." << endl;
    return out;
}

istream &operator>>(istream &in, FileCommandProcessorAdapter &object)
{
    if(!object.fileEmptyFlag) cout << "Utilizing command from file..." << endl;
    string s = "";

    if(!object.fileCollection.empty()) {
        s = *object.fileCollection.begin();
        object.fileCollection.erase(object.fileCollection.begin());        
    }
    
    else {
        if(!object.fileEmptyFlag) {
            cout << "File empty. Commands will require console input from now on.\n Please enter one: ";
            object.fileEmptyFlag = true;
        }
        in >> s;
    }

    object.readCommmand(s);

    return in;
}

