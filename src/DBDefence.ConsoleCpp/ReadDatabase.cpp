#include <iostream>
#include <Windows.h>
//#include <sql.h>
#include <sqlext.h>

#include "StringUtil.h"

// REF: https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/odbc-api-reference?view=sql-server-ver15

bool CheckSQLStatus(const char* sqlFunctionName, SQLRETURN status, SQLHANDLE sqlHandle, SQLSMALLINT sqlHandleType) {
    const int BUFFER_SIZE = 255;

    bool result = status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO;

    if (!result) {
        SQLWCHAR messageText[BUFFER_SIZE] = {};
        SQLWCHAR sqlState[6] = {};
        SQLINTEGER nativeError = 0;
        SQLSMALLINT messageLength = 0;

        std::cout << sqlFunctionName << "(): " << status << "\n";

        //status = SQLGetDiagField();

        status = SQLGetDiagRec(sqlHandleType, sqlHandle, 1, sqlState, &nativeError, messageText, BUFFER_SIZE, &messageLength);

        std::wcout << "SQLGetDiagRec: " << status << "\n";
        std::wcout << "SQL State    : " << std::wstring(sqlState) << "\n";
        std::wcout << "Message      : " << std::wstring(messageText) << "\n";
        std::wcout << "Native Error : " << nativeError << "\n";
    }

    return result;
}

void ReadDatabase(const wchar_t* connectionString) {

    const int BUFFER_SIZE = 255;

    SQLHDBC connectionHandle = SQL_NULL_HDBC;;
    SQLHENV envHandle = SQL_NULL_HENV;
    SQLRETURN status;

    HWND desktopHandle = GetDesktopWindow();

    //status = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &envHandle);
    status = SQLAllocEnv(&envHandle);

    if (CheckSQLStatus("SQLAllocEnv", status, SQL_NULL_HANDLE, SQL_NULL_HANDLE)) {

        //status = SQLAllocHandle(SQL_HANDLE_DBC, envHandle, &connectionHandle);
        status = SQLAllocConnect(envHandle, &connectionHandle);

        if (CheckSQLStatus("SQLAllocConnect", status, envHandle, SQL_HANDLE_ENV)) {

            SQLWCHAR* serverName = (SQLWCHAR*)L".\\SQLEXPRESS";
            SQLWCHAR outConnStr[BUFFER_SIZE];
            SQLSMALLINT outConnStrLen;

            // SQL_DRIVER_COMPLETE - Prompts for info if the connection string is NOT complete
            // SQL_DRIVER_NOPROMPT

            status = SQLDriverConnect(connectionHandle, desktopHandle, (SQLWCHAR*)connectionString, SQL_NTSL, outConnStr, BUFFER_SIZE, &outConnStrLen, SQL_DRIVER_COMPLETE);

            if (CheckSQLStatus("SQLDriverConnect", status, connectionHandle, SQL_HANDLE_DBC)) {

                SQLHSTMT statementHandle = SQL_NULL_HSTMT;

                status = SQLAllocHandle(SQL_HANDLE_STMT, connectionHandle, &statementHandle);

                if (CheckSQLStatus("SQLAllocHandle", status, statementHandle, SQL_HANDLE_STMT)) {

                    SQLWCHAR* selectStatement = (SQLWCHAR*)L"SELECT FirstName, LastName FROM dbo.Contact";

                    status = SQLExecDirect(statementHandle, selectStatement, SQL_NTS);

                    if (CheckSQLStatus("SQLExecDirect", status, statementHandle, SQL_HANDLE_STMT)) {

                        SQLWCHAR firstName[BUFFER_SIZE] = {};
                        SQLWCHAR lastName[BUFFER_SIZE] = {};
                        SQLLEN firstNameLen = 0;
                        SQLLEN lastNameLen = 0;
                        bool endOfData = false;

                        status = SQLBindCol(statementHandle, 1, SQL_C_WCHAR, &firstName, BUFFER_SIZE, &firstNameLen);
                        status = SQLBindCol(statementHandle, 2, SQL_C_WCHAR, &lastName, BUFFER_SIZE, &lastNameLen);

                        std::wcout << L"FirstName, LastName\n";

                        while (!endOfData) {
                            status = SQLFetch(statementHandle);

                            if (status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO) {
                                std::wcout << std::wstring(firstName) << L", " << std::wstring(lastName) << L"\n";
                            } else {
                                endOfData = true;

                                if (status != SQL_NO_DATA) {
                                    CheckSQLStatus("SQLFetch", status, statementHandle, SQL_HANDLE_STMT);
                                }
                            }
                        }
                    }
                }

                status = SQLDisconnect(connectionHandle);
            }

            SQLFreeHandle(SQL_HANDLE_DBC, connectionHandle);
        }
        SQLFreeHandle(SQL_HANDLE_ENV, envHandle);
    }
}