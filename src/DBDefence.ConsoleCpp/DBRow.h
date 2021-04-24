#pragma once

#include <list>

#include "DBColumn.h"

class DBRow {

private:

    list<DBColumn*> _columns;
    SQLHSTMT _statementHandle = SQL_NULL_HSTMT;
    SQLRETURN _status = SQL_SUCCESS;
    wstring _tableName;

public:

    DBRow();
    DBRow(wstring tableName);
    DBRow(SQLHSTMT statementHandle);
    ~DBRow();

    void AddColumn(DBColumn* column);
    SQLRETURN Bind(SQLHSTMT statementHandle);
    wstring ColumnNames(wstring delimiter = L", ");
    wstring ColumnValues(wstring delimiter = L", ");
    void DeleteColumns();

};