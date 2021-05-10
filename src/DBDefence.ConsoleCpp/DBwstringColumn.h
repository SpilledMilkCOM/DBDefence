#pragma once

#include <string>

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

#include "DBColumn.h"

using namespace std;

/// <summary>
/// This class is used to encapsulate a database column.
/// TODO: Promote this to a base class and create subclasses for base datatypes.
/// </summary>

class DBwstringColumn : public DBColumn {

private:

    SQLWCHAR* _buffer = NULL;

public:

    DBwstringColumn(wstring name, int type, int size, int columnNumber);
    DBwstringColumn(SQLHSTMT statementHandle, wstring name, int type, int size, int columnNumber);
    ~DBwstringColumn();

    SQLRETURN Bind(SQLHSTMT statementHandle);

    wstring Value();
};