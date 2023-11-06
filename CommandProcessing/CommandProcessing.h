#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testCommandProcessor();

class Command {
    public:
        //Constructor
        Command();

        Command(string c, string e);

        //Destructor
        ~Command();

        // Copy Constructor
        Command(const Command& c);

        // Operators
        Command& operator=(const Command& c);

        friend ostream& operator<<(ostream& out, const Command& object);

        void saveEffect(string e);

        string getEffect();

        string getCommand();

    private:
        string* command;
        string* effect;
};

class CommandProcessor {
    public: 
        //Constructor
        CommandProcessor();

        CommandProcessor(char type);

        //Destructor
        ~CommandProcessor();

        //Copy Constructor
        CommandProcessor(const CommandProcessor& c);

        //Operators
        CommandProcessor& operator=(const CommandProcessor& c);

        friend ostream& operator<<(ostream& out, const CommandProcessor& object);

        friend istream& operator>>(istream& in, CommandProcessor& object);

        Command* getCommand();

        void setState(string* s);

        bool hasNew();

        void removeNew();

    protected: 
        char* type;

        vector<Command*> commands;

        string* state;

        bool* newCommand;

        void readCommmand(string s);

        void saveCommand(string command, string effect);

        string validate(string command);
};

class FileCommandProcessorAdapter : public CommandProcessor {
    public:
        FileCommandProcessorAdapter(const string& filename);

        //Destructor
        ~FileCommandProcessorAdapter();

        //Copy Constructor
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter& c);

        //Operators
        FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& c);

        friend ostream& operator<<(ostream& out, const FileCommandProcessorAdapter& object);

        friend istream& operator>>(istream& in, FileCommandProcessorAdapter& object);

    private: 
        vector<string> fileCollection;

        bool fileEmptyFlag;
};
