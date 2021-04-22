#include <iostream>
//#include <minwinbase.h>
#include <string>

#include "DbDefenceInit.h"
#include "GetPassword.h"
#include "ProgramArgs.h"
#include "ReadDatabase.h"
#include "StringUtil.h"
//#include "../../../../Windows/Microsoft.NET/Framework/v4.0.30319/mscorlib.dll"

/// <summary>
/// Write the argument count and arguments to the console
/// </summary>
/// <param name="argc">Argument count from the command line</param>
/// <param name="argv">Arguments from the command line</param>
void DumpArgs(int argc, char* argv[]) {
    std::cout << "argc=" << argc << "\n";

    for (int index = 0; index < argc; index++) {
        std::cout << "argv=" << argv[index] << "\n";
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="option"></param>
/// <returns></returns>
int FindOption(int argc, char* argv[], std::string option) {
    int result = -1;

    for (int index = 0; index < argc; index++) {
        if (argv[index] == option) {
            result = index;
            break;
        }
    }

    return result;
}

/// <summary>
/// Parse the command line arguments
/// </summary>
/// <param name="argc">Argument count from the command line</param>
/// <param name="argv">Arguments from the command line</param>
/// <returns>The populated ProgramArgs based on the parsed command line arguments</returns>
ProgramArgs ParseArgs(int argc, char* argv[]) {

    ProgramArgs result = {};

    if (argc > 1) {
        int index = FindOption(argc, argv, "-d");

        if (index >= 0 && index + 1 < argc) {
            result.DatabaseName = argv[index+1];
        }

        index = FindOption(argc, argv, "-p");

        if (index >= 0 && index + 1 < argc) {
            result.Password = argv[index+1];
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::cout << "Hello World!\n";

    DumpArgs(argc, argv);

    ProgramArgs args = ParseArgs(argc, argv);

    if (args.Password.empty()) {
        args.Password = GetPassword("\nEnter the password: ", '*');
    }

    std::cout << "Database Name: \"" << args.DatabaseName << "\"\n";
    std::cout << "Password     : \"" << args.Password << "\"\n";

    wchar_t* databaseName = _wcsdup(ConvertToWideString(args.DatabaseName).c_str());
    wchar_t* password = _wcsdup(ConvertToWideString(args.Password).c_str());

    //InitializeDBDefence(databaseName, password);

    ReadDatabase();

    free(databaseName);
    free(password);
}