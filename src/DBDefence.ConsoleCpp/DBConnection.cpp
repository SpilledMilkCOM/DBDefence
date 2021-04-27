#include "DBConnection.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBConnection::DBConnection() {
    _sqlUtilAllocated = true;
    _sqlUtil = new SQLUtil();
}

DBConnection::DBConnection(wstring connectionString, SQLUtil* sqlUtil) {

    if (sqlUtil == NULL) {
        throw new exception("'sqlUtil' must be defined.");
    }

    _connectionString = connectionString;
    _sqlUtilAllocated = false;
    _sqlUtil = sqlUtil;
}

DBConnection::~DBConnection() {

    if (_envHandle != SQL_NULL_HENV) {
        SQLFreeHandle(SQL_HANDLE_ENV, _envHandle);
        _envHandle = SQL_NULL_HENV;
    }

    if (_connectionHandle != SQL_NULL_HDBC) {
        SQLFreeHandle(SQL_HANDLE_DBC, _connectionHandle);
        _connectionHandle = SQL_NULL_HDBC;
    }

    if (_sqlUtilAllocated) {
        if (_sqlUtil != NULL) {
            delete(_sqlUtil);
            _sqlUtil = NULL;
        }
    }
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

bool
DBConnection::Connect() {

    const int BUFFER_SIZE = 255;

    bool result = false;

    HWND desktopHandle = GetDesktopWindow();   // Does this need to be free()'d ???

    //_status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &envHandle);
    _status = SQLAllocEnv(&_envHandle);

    if (_sqlUtil->CheckSQLStatus("SQLAllocEnv", _status, SQL_NULL_HANDLE, SQL_NULL_HANDLE)) {

        _status = SQLAllocHandle(SQL_HANDLE_DBC, _envHandle, &_connectionHandle);

        if (_sqlUtil->CheckSQLStatus("SQLAllocConnect", _status, _envHandle, SQL_HANDLE_ENV)) {

            SQLWCHAR outConnStr[BUFFER_SIZE];
            SQLSMALLINT outConnStrLen;

            // SQL_DRIVER_COMPLETE - Prompts for info if the connection string is NOT complete
            // SQL_DRIVER_NOPROMPT

            _status = SQLDriverConnect(_connectionHandle, desktopHandle, (SQLWCHAR*)_connectionString.c_str(), SQL_NTSL, outConnStr, BUFFER_SIZE, &outConnStrLen, SQL_DRIVER_COMPLETE);

            result = _sqlUtil->CheckSQLStatus("SQLDriverConnect", _status, _connectionHandle, SQL_HANDLE_DBC);
        }
    }

    return _status;
}

bool
DBConnection::Disconnect() {
    return _status = SQLDisconnect(_connectionHandle);
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

SQLHDBC
DBConnection::ConnectionHandle() {
    return _connectionHandle;
}

wstring
DBConnection::ConnectionString() {
    return _connectionString;
}

wstring
DBConnection::ConnectionString(wstring connectionString) {

    wstring result = _connectionString;

    _connectionString = connectionString;

    return result;
}

SQLRETURN
DBConnection::Status() {
    return _status;
}