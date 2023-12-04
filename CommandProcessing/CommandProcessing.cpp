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

const string acceptedConsoleCommands[15][3] = {
    {"tournament", "START", "WIN"},
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
    {"quit", "WIN", "END"}};

const string acceptedPlayerCommands[7][2] = {
    {"Reinforce", "ASSIGN_REINFORCEMENT"},
    {"Advance", "ISSUE_ORDERS"},
    {"Deploy", "ISSUE_ORDERS"},
    {"Airlift", "ISSUE_ORDERS"},
    {"Bomb", "ISSUE_ORDERS"},
    {"Blockade", "ISSUE_ORDERS"},
    {"Negotiate", "ISSUE_ORDERS"}};

// FREE FUNCTION

void testCommandProcessor()
{
    cout << "TESTING PLAYER COMMANDS: " << endl;

    Player *p = new Player();
    p->setName("test");

    p->testState("ISSUE_ORDERS");

    p->play();
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
    // Notifies observers
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

// For game log
string Command::stringToLog()
{
    return "Commands Effect: " + effect + " was just saved.";
}

// CONSOLE COMMAND PROCESSING

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
{
}

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
    if (!commands.empty())
    {
        return commands.back();
    }
    else
        return c;
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

// For game log
string CommandProcessor::stringToLog()
{
    if (!commands.empty())
    {
        Command lastCommand = commands.back();
        string logString;

        logString = "Command: " + lastCommand.getCommand() + " was just saved.";
        return logString;
    }
    else
    {
        cout << "No commands in the vector to log." << endl;
        return "No commands in the vector to log.";
    }
}

void CommandProcessor::testSaveCommand(string c, string e)
{
    saveCommand(c, e);
}

void CommandProcessor::processTournamentCommand(string input)
{
    vector<string> tournamentCommand = split(input, ' ');
    vector<string> temp;
    string directive = "";

    for(int i = 1; i < tournamentCommand.size(); i++) {
        if(tournamentCommand[i] == "-M" || tournamentCommand[i] == "-P" ||
            tournamentCommand[i] == "-G" || tournamentCommand[i] == "-D") {
                if(tournamentCommand[i] == "-P") tournamentListOfMapFiles = temp;
                if(tournamentCommand[i] == "-G") tournamentListOfPlayerStrategies = temp;
                if(tournamentCommand[i] == "-D") tournamentNumberOfGames = stoi(temp.at(0));

                temp.clear();
            }
        
        else temp.push_back(tournamentCommand.at(i));
    }

    tournamentMaxNumberOfTurns = stoi(temp.at(0));
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

// VALIDATE COMMANDS
string CommandProcessor::validate(string command)
{
    cout << "VALIDATING COMMAND... " << endl;

    // CONSOLE COMMAND VALIDATION
    if (type == 'c')
    {
        cout << "Scanning console commands... ";
        for (int i = 0; i < sizeof(acceptedConsoleCommands); i++)
        {
            // Check if console level command or game level command
            if (acceptedConsoleCommands[i][0] == command)
            {

                cout << "Correct Console command: " << command << "." << endl;
                cout << state;

                if (acceptedConsoleCommands[i][1] == state)
                {
                    cout << "Correct state " << state << ". Validated." << endl;
                    return acceptedConsoleCommands[i][2];
                }
            }
        }
    }

    // PLAYER COMMAND VALIDATION
    else
    {
        cout << "Scanning player commands... ";

        for (int i = 0; i < sizeof(acceptedPlayerCommands); i++)
        {
            if (acceptedPlayerCommands[i][0] == command)
            {

                cout << "Correct Player command: " << command << "." << endl;

                if (acceptedPlayerCommands[i][1] == state)
                {
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

    if (newCommand)
        cout << "true" << endl;

    if (effect != "ERROR: Invalid Command")
    {
        cout << "SAVING COMMAND... " << endl;
        newCommand = true;
    }

    else
    {
        cout << "SAVING ERROR... " << endl;
    }

    commands.push_back(Command(command, effect));

    // Notifies observers
    notify(this);

    cout << "Saved Console command: " << commands.back() << endl;
}

// FILE COMMAND ADAPTER

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string &filename)
{
    newCommand = false;
    fileEmptyFlag = false;

    ifstream file(".\\" + filename);

    if (!file.is_open())
    {
        throw runtime_error("Error: Unable to open file " + filename);
    }

    string line;

    while (getline(file, line))
    {
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
    if (!object.fileEmptyFlag)
        cout << "Utilizing command from file..." << endl;
    string s = "";

    if (!object.fileCollection.empty())
    {
        s = *object.fileCollection.begin();
        object.fileCollection.erase(object.fileCollection.begin());
    }

    else
    {
        if (!object.fileEmptyFlag)
        {
            cout << "File empty. Commands will require console input from now on.\n Please enter one: ";
            object.fileEmptyFlag = true;
        }
        in >> s;
    }

    object.readCommmand(s);

    return in;
}

vector<string> CommandProcessor::split(string s, char delimiter)
{
    vector<string> res;

    string temp = "";
    for(auto i : s) {
        if(i == delimiter) {
            res.push_back(temp);
            temp = "";
        }
        else temp += i;
    }

    res.push_back(temp);

    return res;
}

vector<string> CommandProcessor::getTournamentListOfMapFiles()
{
    return tournamentListOfMapFiles;
}

void CommandProcessor::addMapFile(string s)
{
    tournamentListOfMapFiles.push_back(s);
    cout << "works";
}

vector<string> CommandProcessor::getTournamentListOfPlayerStrategies()
{
    return tournamentListOfPlayerStrategies;
}

void CommandProcessor::addStrategy(string s)
{
    tournamentListOfPlayerStrategies.push_back(s);
}

int CommandProcessor::getTournamentNumberOfGames()
{
    return tournamentNumberOfGames;
}

void CommandProcessor::setGames(int i)
{
    tournamentNumberOfGames = i;
}

int CommandProcessor::getTournamentMaxNumberOfTurns()
{
    return tournamentMaxNumberOfTurns;
}

void CommandProcessor::setTurns(int i)
{
    tournamentMaxNumberOfTurns = i;
}
