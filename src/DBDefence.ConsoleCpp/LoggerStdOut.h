#pragma once

#include "ILogger.h"

using namespace std;

/// <summary>
/// This class implements the ILogger interface and abstracts out the logging so all of the classes are not including <iostream>
/// </summary>

class LoggerStdOut : public ILogger {

public:

    LoggerStdOut();

    // Even though the methods are defined in the interface, you need to tell the compiler that you WILL be implementing these in this class.

    void Log(string message);
    void Log(wstring message);
};