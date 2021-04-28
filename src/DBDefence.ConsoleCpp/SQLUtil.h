#pragma once

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

#include "ILogger.h"

class SQLUtil {

private:

    ILogger* _logger;
    bool _loggerAllocated = false;
 
public:
    SQLUtil(ILogger* logger = NULL);
    ~SQLUtil();

    bool CheckSQLStatus(const char* sqlFunctionName, SQLRETURN status, SQLHANDLE sqlHandle, SQLSMALLINT sqlHandleType);
};