#pragma once

#include <string>

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

#include "LoggerStdOut.h"
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
    LoggerStdOut* _logger = NULL;
    bool _loggerAllocated = false;
    SQLUtil* _sqlUtil = NULL;
    SQLRETURN _status = SQL_SUCCESS;

public:

    DBConnection();
    DBConnection(wstring connectionString, SQLUtil* sqlUtil, LoggerStdOut* logger = NULL);
    ~DBConnection();

    SQLRETURN Connect();

    wstring ConnectionString();
    wstring ConnectionString(wstring connectionString);
};