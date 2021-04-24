#include "DBConnection.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBConnection::DBConnection() {
    _loggerAllocated = true;
    _logger = new LoggerStdOut();
    _sqlUtil = new SQLUtil(_logger);
}

DBConnection::DBConnection(wstring connectionString, SQLUtil* sqlUtil, LoggerStdOut* logger) {

    if (sqlUtil == NULL) {
        throw new exception("'sqlUtil' must be defined.");
    }

    if (logger == NULL) {
        throw new exception("'logger' must be defined.");
    }

    _connectionString = connectionString;
    _loggerAllocated = false;
    _logger = logger;
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

    if (_loggerAllocated) {
        if (_logger != NULL) {
            delete(_logger);
            _logger = NULL;
        }
        if (_sqlUtil != NULL) {
            delete(_sqlUtil);
            _sqlUtil = NULL;
        }
    }
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

SQLRETURN
DBConnection::Connect() {

    HWND desktopHandle = GetDesktopWindow();   // Does this need to be free()'d ???

    _status = SQLAllocEnv(&_envHandle);

    return _status;
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

wstring
DBConnection::ConnectionString() {
    return _connectionString;
}

wstring DBConnection::ConnectionString(wstring connectionString) {

    wstring result = _connectionString;

    _connectionString = connectionString;

    return result;
}