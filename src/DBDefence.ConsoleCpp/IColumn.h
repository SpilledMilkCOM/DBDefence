#pragma once

#include <string>

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

using namespace std;

/// <summary>
/// This is an "interface" class which is abstract (contains at least one pure virtual method).
/// In an "interface" ALL of the methods should be pure virtual so you HAVE TO implement ALL of the methods.
/// There is NO .cpp file for this interface, because there is NO underlying code for it.
/// </summary>

class IColumn {

public:

    virtual SQLRETURN Bind(SQLHSTMT statementHandle) = 0;

    virtual wstring Name() = 0;
    virtual SQLRETURN Status() = 0;
    virtual wstring Value() = 0;
};