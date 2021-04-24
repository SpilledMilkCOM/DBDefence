#pragma once

#include "DBRow.h"
#include "SQLUtil.h"

/// <summary>
/// A pure virtual class that encapsulates reading a SQL statement
/// </summary>
class DBTable {

protected:

    // The current fetched row.
    DBRow* _row;

private:

    LoggerStdOut* _logger = NULL;
    bool _allocatedDefault = false;
    SQLUtil* _sqlUtil = NULL;
    SQLHSTMT _statementHandle = SQL_NULL_HSTMT;
    SQLRETURN _status = SQL_SUCCESS;
    wstring _tableName;

public:

    DBTable();
    DBTable(wstring tableName, SQLUtil* sqlUtil);
    ~DBTable();

    virtual void OutputRow() = 0;
    void Read();

protected:


};