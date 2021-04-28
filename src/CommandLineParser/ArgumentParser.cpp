#include "pch.h"

#include "ArgumentParser.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

ArgumentParser::ArgumentParser(string programName) {
    _programName = programName;
}

ArgumentParser::~ArgumentParser() {
    DeleteOptions();
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

/// <summary>
/// Add an option to the known options for the parser
/// Cannot add duplicate options
/// </summary>
/// <param name="option">An option</param>
/// <returns>If the option was added or not</returns>
bool
ArgumentParser::AddOption(ArgumentOption* option) {
    if (option == NULL) {
        throw exception("'option' must be defined.");
    }

    bool added = !HasOption(option->Option());

    if (added) {
        _options.push_back(option);
    }

    return added;
}

/// <summary>
/// Deletes the options from memory
/// </summary>
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

/// <summary>
/// Get the value of a parsed option
/// </summary>
/// <param name="optionFlag">Designated option</param>
/// <returns>The value of the found option (empty if not found)</returns>
string
ArgumentParser::GetValue(string optionFlag) {
    ArgumentOption* option = FindOption(optionFlag);
    string result;

    if (option != NULL) {
        result = option->Value();

        if (result.empty() && option->Required()) {
            string message = "The option '" + optionFlag + "' is required.";

            throw exception(message.c_str());
        }
    }

    return result;
}

/// <summary>
/// Check whether the option was found during parsing.
/// </summary>
/// <param name="option">The Option</param>
/// <returns>Found during parsing or not.</returns>
bool
ArgumentParser::HasOption(string optionFlag) {
    ArgumentOption* option = FindOption(optionFlag);
    bool result = false;

    if (option != NULL) {
        result = option->Found();
    }

    return result;
}

void
ArgumentParser::Parse(int argc, char* argv[]) {

    for (ArgumentOption* option : _options) {
        int index = FindArgument(option->Option(), argc, argv);

        option->Found(index >= 0);

        // If the option was found and there is another argument that is NOT an option.
        // ex:  program.exe -a aValue -b -c
        // *** -c CANNOT be the value for -b (if -c is defined as an option) ***

        if (index >= 0 && index + 1 < argc && FindOption(argv[index+1]) == NULL) {

            option->Value(argv[index+1]);
        }
    }

    // TODO: Look for missing required options here.
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
string
ArgumentParser::Usage() {
    string result = "Usage: " + _programName + " ";

    for (ArgumentOption* option : _options) {
        if (option->Required()) {
            result += "<";
        } else {
            result += "[";
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

    result += "\n";

    for (ArgumentOption* option : _options) {
        result += "\n" + option->Option() + "  " + option->Description();

        // TODO: Make the description line up (prettier)
    }

    result += "\n[]  Argument is optional.";

    return result;
}

//----==== PRIVATE ====----------------------------------------------------------------------------

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