#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>

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

//TODO: ADD COMMANDS FOR PLAYERS
//const string acceptedPlayer 

// COMMAND
Command::Command(string c, string e)
{
    command = c;
    this->saveEffect(e);
}

ostream &operator<<(ostream &out, const Command &object)
{
    out << "Command: " << object.command << " -> Effect: " << object.effect << endl;
    return out;
}

void Command::saveEffect(string e)
{
    effect = e;
}

string Command::getEffect()
{
    return effect;
}

string Command::getCommand()
{
    return command;
}

//CONSOLE COMMAND PROCESSING

CommandProcessor::CommandProcessor()
{
    newCommand = false;
}

Command* CommandProcessor::getCommand()
{
    Command * c = new Command("empty", "None");
    if(!commands.empty()){
        return commands.back();
    }
    else return c;
}

void CommandProcessor::setState(string *s)
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

    // Validate
    if(validate(s)) 
        // If true save
        saveCommand(s);

    else saveError(s);
}

bool CommandProcessor::validate(string command)
{
    cout << "VALIDATING COMMAND... " << endl;

    for(int i= 0; i < sizeof(acceptedConsoleCommands); i++) {
        //Check if console level command or game level command
        if(acceptedConsoleCommands[i][0].find(command) != std::string::npos) {

            cout << "Correct command: " << command << "." << endl;

            if(acceptedConsoleCommands[i][1] == *state) {
                cout << "Correct state " << *state << ". Validated." << endl;
                return true;
            }

            if(i >= 8) return true;
        }
    }

    cout << "Command invalid." << endl;

    return false;
}

void CommandProcessor::saveCommand(string s)
{
    cout << "SAVING COMMAND... " << endl;
    
    for(int i= 0; i < sizeof(acceptedConsoleCommands); i++) {
        if(acceptedConsoleCommands[i][0].find(s) != std::string::npos) {
            Command* c = new Command(s, acceptedConsoleCommands[i][2]);
            commands.push_back(c);
            cout << "Saved command: " << *commands.back() << endl;
            newCommand = true;
            return;
        }
    }
}

void CommandProcessor::saveError(string s)
{
    cout << "SAVING ERROR... " << endl;

    commands.push_back(new Command(s, "ERROR: Invalid Command"));

    cout << *commands.back() << endl;
}

