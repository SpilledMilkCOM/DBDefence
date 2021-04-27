#pragma once

#include <list>

#include "ArgumentOption.h"

class ArgumentParser {

private:

    string _programName;
    list<ArgumentOption*> _options;

public:

    ArgumentParser(string programName);
    ~ArgumentParser();

    bool AddOption(ArgumentOption* option);
    void DeleteOptions();
    string DumpArgs(int argc, char* argv[]);
    string GetValue(string option);
    bool HasOption(string option);
    void Parse(int argc, char* argv[]);
    string Usage();

private:

    int FindArgument(string option, int argc, char* argv[]);
    ArgumentOption* FindOption(string option);
};