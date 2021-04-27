#include "ArgumentParser.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

ArgumentParser::ArgumentParser(string programName) {
    _programName = programName;
}

ArgumentParser::~ArgumentParser() {
    DeleteOptions();
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

void
ArgumentParser::AddOption(ArgumentOption* option) {
    _options.push_back(option);
}

void
ArgumentParser::DeleteOptions() {
    for (ArgumentOption* option : _options) {
        delete(option);
    }
    _options.clear();
}

/// <summary>
/// Write the argument count and arguments to the console
/// </summary>
/// <param name="argc">Argument count from the command line</param>
/// <param name="argv">Arguments from the command line</param>
string
ArgumentParser::DumpArgs(int argc, char* argv[]) {

    string result = "argc=" + to_string(argc) + "\n";

    for (int index = 0; index < argc; index++) {
        result += "argv[" + to_string(index) + "]=" + string(argv[index]) + "\n";
    }

    return result;
}

string
ArgumentParser::GetValue(string optionFlag) {
    ArgumentOption* option = FindOption(optionFlag);
    string result;

    if (option != NULL) {
        result = option->Value();

        if (result.empty() && option->Required()) {
            string message = "The option '" + optionFlag + "' is required.";

            throw new exception(message.c_str());
        }
    }

    return result;
}

void
ArgumentParser::Parse(int argc, char* argv[]) {

    for (ArgumentOption* option : _options) {
        int index = FindArgument(option->Option(), argc, argv);

        if (index >= 0 && index + 1 < argc) {
            option->Value(argv[index+1]);
        }
    }

    // TODO: Look for missing required options here.
}

string
ArgumentParser::Usage() {
    string result = "Usage: " + _programName;

    for (ArgumentOption* option : _options) {
        if (option->Required()) {
            result += " <";
        } else {
            result += " [";
        }
            
        result += option->Option();

        if (!option->ValueName().empty()) {
            result += " " + option->ValueName();
        }

        if (option->Required()) {
            result += ">";
        } else {
            result += "]";
        }
    }

    for (ArgumentOption* option : _options) {
        result += "\n" + option->Option() + "  " + option->Description();

        // TODO: Make the description line up (prettier)
    }

    return result;
}

int
ArgumentParser::FindArgument(string option, int argc, char* argv[]) {
    int result = -1;

    for (int index = 0; index < argc; index++) {
        if (argv[index] == option) {
            result = index;
            break;
        }
    }

    return result;
}

ArgumentOption*
ArgumentParser::FindOption(string optionFlag) {
    ArgumentOption* result = NULL;

    for (ArgumentOption* option : _options) {
        if (option->Option().compare(optionFlag.c_str()) == 0) {
            result = option;
            break;
        }
    }

    return result;
}