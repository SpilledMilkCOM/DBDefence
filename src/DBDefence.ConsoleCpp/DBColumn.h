#pragma once

#include <string>

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

using namespace std;

/// <summary>
/// This class is used to encapsulate a database column.
/// TODO: Promote this to a base class and create subclasses for base datatypes.
/// </summary>

class DBColumn {

private:

    unsigned int _columnNumber = 0;
    unsigned int _size = 0;
    unsigned int _type = 0;

    string _name;
    SQLWCHAR* _buffer = NULL;
    SQLRETURN _status = SQL_SUCCESS;

public:

    DBColumn(string name, int type, int size, int columnNumber);
    DBColumn(SQLHSTMT statementHandle, string name, int type, int size, int columnNumber);
    ~DBColumn();

    SQLRETURN Bind(SQLHSTMT statementHandle);

    string Name();
    SQLRETURN Status();
    wstring Value();
};