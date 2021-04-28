#pragma once

#include <string>

using namespace std;

/// <summary>
/// This class abstracts out the logging so all of the classes are not including <iostream>
/// </summary>

class ILogger {

public:

    virtual void Log(string message) = 0;
    virtual void Log(wstring message) = 0;
};