#pragma once

#include "DBStatement.h"
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

    bool _allocatedDefault = false;
    DBConnection* _connection = NULL;
    ILogger* _logger = NULL;
    SQLUtil* _sqlUtil = NULL;
    DBStatement* _statement = NULL;
    SQLRETURN _status = SQL_SUCCESS;
    wstring _tableName;

public:

    DBTable(DBConnection* connection);
    DBTable(DBConnection* connection, wstring tableName, SQLUtil* sqlUtil);
    ~DBTable();

    virtual void OutputRow() = 0;
    void Read();

    wstring Statement();
    wstring Statement(wstring statement);

protected:


};