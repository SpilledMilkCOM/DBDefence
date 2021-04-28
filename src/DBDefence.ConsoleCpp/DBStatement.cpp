#include "DBStatement.h"

DBStatement::DBStatement(wstring statement, DBConnection* connection, DBRow* row, SQLUtil* sqlUtil) {

    if (statement.empty()) {
        throw exception("'statement' must be defined.");
    }

    if (connection == NULL) {
        throw exception("'connection' must be defined.");
    }

    if (row == NULL) {
        throw exception("'row' must be defined.");
    }

    if (sqlUtil == NULL) {
        throw exception("'sqlUtil' must be defined.");
    }

    _row = row;
    _sqlUtil = sqlUtil;

    _status = SQLAllocHandle(SQL_HANDLE_STMT, connection->ConnectionHandle(), &_statementHandle);

    if (_sqlUtil->CheckSQLStatus("SQLAllocHandle", _status, connection->ConnectionHandle(), SQL_HANDLE_STMT)) {

        Statement(statement);
    }
}

DBStatement::~DBStatement() {
    if (_statementHandle != SQL_NULL_HSTMT) {
        SQLFreeHandle(SQL_HANDLE_STMT, _statementHandle);
        _statementHandle = SQL_NULL_HSTMT;
    }
}

wstring
DBStatement::Statement() {
    return _statement;
}

wstring
DBStatement::Statement(wstring statement) {
    wstring result = _statement;

    _statement = statement;

    _status = SQLExecDirect(_statementHandle, (SQLWCHAR*)_statement.c_str(), SQL_NTS);

    if (_sqlUtil->CheckSQLStatus("SQLExecDirect", _status, _statementHandle, SQL_HANDLE_STMT)) {

        _row->Bind(_statementHandle);
    }

    return result;
}

bool
DBStatement::Fetch() {
    bool result = false;

    _status = SQLFetch(_statementHandle);

    result = _status == SQL_SUCCESS || _status == SQL_SUCCESS_WITH_INFO;

    if (_status != SQL_NO_DATA) {
        _sqlUtil->CheckSQLStatus("SQLFetch", _status, _statementHandle, SQL_HANDLE_STMT);
    }

    return result;
}