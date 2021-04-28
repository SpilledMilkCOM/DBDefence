#include <iostream>
#include <string>

#include "ArgumentParser.h"
#include "DbDefenceInit.h"
#include "GetPassword.h"
#include "ProgramConfiguration.h"
#include "ReadDatabase.h"
#include "StringUtil.h"

const string CONNECTION_OPTION = "-c";
const string DATABASE_OPTION = "-d";
const string PASSWORD_OPTION = "-p";
const string USAGE_OPTION = "-?";

using namespace std;

/// <summary>
/// Add all of the arguments to the parser
/// </summary>
/// <param name="argParser">The argument parser</param>
void
InitializeArguments(ArgumentParser* argParser) {

    argParser->AddOption(new ArgumentOption(CONNECTION_OPTION, "ConnectionString", "The full connection string of the database.", true));
    argParser->AddOption(new ArgumentOption(DATABASE_OPTION, "DatabaseName", "The name of the encrypted database.", false));
    argParser->AddOption(new ArgumentOption(PASSWORD_OPTION, "Password", "The password of the encrypted database.", false));
    argParser->AddOption(new ArgumentOption(USAGE_OPTION, "", "Display this usage statement.", false));
}

/// <summary>
/// Parse the command line arguments
/// </summary>
/// <param name="argParser">Argument parser</param>
/// <param name="argc">Argument count from the command line</param>
/// <param name="argv">Arguments from the command line</param>
/// <param name="programConfig">Program configuration to populate</param>
/// <returns>Whether or not the program configuration was populated.</returns>
bool
ParseArgs(ArgumentParser* argParser, int argc, char* argv[], ProgramConfiguration* programConfig) {
    bool result = false;

    InitializeArguments(argParser);

    argParser->Parse(argc, argv);

    result = !argParser->HasOption(USAGE_OPTION);

    if (result) {
        programConfig->ConnectionString = argParser->GetValue(CONNECTION_OPTION);
        programConfig->DatabaseName = argParser->GetValue(DATABASE_OPTION);
        programConfig->Password = argParser->GetValue(PASSWORD_OPTION);
    }

    return result;
}

int
main(int argc, char* argv[]) {
    // Command arguments:
    // -d TestDBEncrypted -p Id.Like.2.Encrypt_This!NOW! -c "Driver={ODBC Driver 11 for SQL Server}; Server=localhost\SQLExpress; Database=TestDBEncrypted; Trusted_Connection=Yes; MultipleActiveResultSets=True"
    // -?

    ArgumentParser argParser("DbDecrypt");
    ProgramConfiguration programConfig;

    cout << argParser.DumpArgs(argc, argv);

    if (!ParseArgs(&argParser, argc, argv, &programConfig)) {

        cout << endl << argParser.Usage() << endl;

        return -1;
    }

    if (programConfig.Password.empty()) {
        programConfig.Password = GetPassword("\nEnter the password: ", '*');
    }

    cout << "\n";
    cout << "Database Name: \"" << programConfig.DatabaseName << "\"\n";
    cout << "Password     : \"" << programConfig.Password << "\"\n\n\n";

    // Need a non-const wchar_t* for InitializeDBDefence()

    wchar_t* databaseName = ConvertToWideCharT(programConfig.DatabaseName);
    wchar_t* password = ConvertToWideCharT(programConfig.Password);
    const wchar_t* dllPath = LR"(C:\tmp\DbDefence\dbd_clnt.dll)";

    InitializeDBDefence(databaseName, password, dllPath);

    ReadDatabase(ConvertToWideString(programConfig.ConnectionString));

    free(databaseName);
    free(password);

    return 0;
}