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

class DBintColumn : public DBColumn {

private:

    int _value = 0;

public:

    DBintColumn(wstring name, int columnNumber);
    DBintColumn(SQLHSTMT statementHandle, wstring name, int columnNumber);
    ~DBintColumn();

    SQLRETURN Bind(SQLHSTMT statementHandle);

    wstring Value();
};