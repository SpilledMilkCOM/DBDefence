#pragma once

#include <string>

using namespace std;

/// <summary>
/// This is an "interface" class which is abstract (contains at least one pure virtual method).
/// In an "interface" ALL of the methods should be pure virtual so you HAVE TO implement ALL of the methods.
/// There is NO .cpp file for this interface, because there is NO underlying code for it.
/// </summary>

class ILogger {

public:

    virtual void Log(string message) = 0;
    virtual void Log(wstring message) = 0;
};