#include <iostream>
//#include <minwinbase.h>
#include <string>

#include "ArgumentParser.h"
#include "DbDefenceInit.h"
#include "GetPassword.h"
#include "ProgramConfiguration.h"
#include "ReadDatabase.h"
#include "StringUtil.h"
//#include "../../../../Windows/Microsoft.NET/Framework/v4.0.30319/mscorlib.dll"

const string CONNECTION_OPTION = "-c";
const string DATABASE_OPTION = "-d";
const string PASSWORD_OPTION = "-p";

using namespace std;

void InitializeArguments(ArgumentParser* argParser) {

    argParser->AddOption(new ArgumentOption(CONNECTION_OPTION, "ConnectionString", "The full connection string of the database.", true));
    argParser->AddOption(new ArgumentOption(DATABASE_OPTION, "DatabaseName", "The name of the encrypted database.", true));
    argParser->AddOption(new ArgumentOption(PASSWORD_OPTION, "Password", "The password of the encrypted.", true));
}

/// <summary>
/// Parse the command line arguments
/// </summary>
/// <param name="argc">Argument count from the command line</param>
/// <param name="argv">Arguments from the command line</param>
/// <returns>The populated ProgramArgs based on the parsed command line arguments</returns>
ProgramConfiguration ParseArgs(ArgumentParser* argParser, int argc, char* argv[]) {
    ProgramConfiguration result = {};

    InitializeArguments(argParser);

    argParser->Parse(argc, argv);

    result.ConnectionString = argParser->GetValue(CONNECTION_OPTION);
    result.DatabaseName = argParser->GetValue(DATABASE_OPTION);
    result.Password = argParser->GetValue(PASSWORD_OPTION);

    return result;
}

int main(int argc, char* argv[]) {
    // Command arguments:
    // -d TestDBEncrypted -p Id.Like.2.Encrypt_This!NOW! -c "Driver={ODBC Driver 11 for SQL Server}; Server=localhost\SQLExpress; Database=TestDBEncrypted; Trusted_Connection=Yes; MultipleActiveResultSets=True"

    ArgumentParser argParser("DbDecrypt");

    cout << argParser.DumpArgs(argc, argv);

    ProgramConfiguration args = ParseArgs(&argParser, argc, argv);

    if (args.Password.empty()) {
        args.Password = GetPassword("\nEnter the password: ", '*');
    }

    cout << "\n";
    cout << "Database Name: \"" << args.DatabaseName << "\"\n";
    cout << "Password     : \"" << args.Password << "\"\n\n\n";

    wchar_t* connectionString = ConvertToWideCharT(args.ConnectionString);
    wchar_t* databaseName = ConvertToWideCharT(args.DatabaseName);
    wchar_t* password = ConvertToWideCharT(args.Password);
    const wchar_t* dllPath = LR"(C:\tmp\DbDefence\dbd_clnt.dll)";

    InitializeDBDefence(databaseName, password, dllPath);

    ReadDatabase(connectionString);

    free(connectionString);
    free(databaseName); 
    free(password);
}