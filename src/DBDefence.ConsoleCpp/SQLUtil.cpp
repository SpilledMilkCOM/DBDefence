#include "SQLUtil.h"
#include "StringUtil.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

SQLUtil::SQLUtil(LoggerStdOut* logger) {
    _loggerAllocated = logger == NULL;
    // Where the hell is coalesce??
    _logger = (_loggerAllocated) ? new LoggerStdOut : logger;
}

SQLUtil::~SQLUtil() {
    if (_loggerAllocated) {
        if (_logger != NULL) {
            delete(_logger);
            _logger = NULL;
        }
    }
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

bool
SQLUtil::CheckSQLStatus(const char* sqlFunctionName, SQLRETURN status, SQLHANDLE sqlHandle, SQLSMALLINT sqlHandleType) {

    const int BUFFER_SIZE = 255;

    bool result = status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO;

    if (!result) {
        SQLWCHAR messageText[BUFFER_SIZE] = {};
        SQLWCHAR sqlState[6] = {};
        SQLINTEGER nativeError = 0;
        SQLSMALLINT messageLength = 0;
        wstring message = ConvertToWideString(string(sqlFunctionName)) + L"(): " + to_wstring(status);

        _logger->Log(message);

        status = SQLGetDiagRec(sqlHandleType, sqlHandle, 1, sqlState, &nativeError, messageText, BUFFER_SIZE, &messageLength);

        message = L"SQLGetDiagRec: " + to_wstring(status) + L"\n";
        message += L"SQL State    : " + wstring(sqlState) + L"\n";
        message += L"Message      : " + wstring(messageText) + L"\n";
        message += L"Native Error : " + to_wstring(nativeError);

        _logger->Log(message);
    }

    return result;
}