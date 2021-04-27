#pragma once

#include "DBConnection.h"
#include "DBRow.h"

class DBStatement {

private:

    DBRow* _row = NULL;
    SQLUtil* _sqlUtil = NULL;
    wstring _statement;
    SQLHSTMT _statementHandle = SQL_NULL_HSTMT;
    SQLRETURN _status = SQL_SUCCESS;

public:

    DBStatement(wstring statement, DBConnection* connection, DBRow* row, SQLUtil* sqlUtil);
    ~DBStatement();

    wstring Statement();
    wstring Statement(wstring statement);

    bool Fetch();
};