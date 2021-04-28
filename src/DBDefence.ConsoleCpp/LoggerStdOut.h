#pragma once

#include "ILogger.h"

using namespace std;

/// <summary>
/// This class abstracts out the logging so all of the classes are not including <iostream>
/// </summary>

class LoggerStdOut : public ILogger {

public:

    void Log(string message);
    void Log(wstring message);
};