#pragma once

#include <string>

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

#include "SQLUtil.h"

using namespace std;

/// <summary>
/// Encapsulates the SQL environment and connection handles (not shared)
/// </summary>
class DBConnection {

private:

    SQLHDBC _connectionHandle = SQL_NULL_HDBC;
    wstring _connectionString;
    SQLHENV _envHandle = SQL_NULL_HENV;
    SQLUtil* _sqlUtil = NULL;
    bool _sqlUtilAllocated = false;
    SQLRETURN _status = SQL_SUCCESS;

public:

    DBConnection();
    DBConnection(wstring connectionString, SQLUtil* sqlUtil);
    ~DBConnection();

    bool Connect();
    bool Disconnect();

    SQLHDBC ConnectionHandle();
    wstring ConnectionString();
    wstring ConnectionString(wstring connectionString);
    SQLRETURN Status();
};