#pragma once

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

#include "LoggerStdOut.h"

class SQLUtil {

private:

    LoggerStdOut* _logger;
    bool _loggerAllocated = false;
 
public:
    SQLUtil(LoggerStdOut* logger = NULL);
    ~SQLUtil();

    bool CheckSQLStatus(const char* sqlFunctionName, SQLRETURN status, SQLHANDLE sqlHandle, SQLSMALLINT sqlHandleType);
};