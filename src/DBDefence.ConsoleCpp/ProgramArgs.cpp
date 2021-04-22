#include <string>

/// <summary>
/// This structure contains all of the arguments that the program will use.
/// A string is used since command line arguments are char* and wchar_t*
/// </summary>

struct ProgramArgs {
    std::string ConnectionString;
    std::string DatabaseName;
    std::string Password;
};