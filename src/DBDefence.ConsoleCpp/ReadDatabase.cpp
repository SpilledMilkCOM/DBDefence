#include <iostream>
#include <Windows.h>
#include <sqlext.h>

#include "ContactTable.h"
#include "DBConnection.h"
#include "DBRow.h"
#include "DBwstringColumn.h"
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

        cout << sqlFunctionName << "(): " << status << "\n";

        //status = SQLGetDiagField();

        status = SQLGetDiagRec(sqlHandleType, sqlHandle, 1, sqlState, &nativeError, messageText, BUFFER_SIZE, &messageLength);

        wcout << "SQLGetDiagRec: " << status << "\n";
        wcout << "SQL State    : " << wstring(sqlState) << "\n";
        wcout << "Message      : " << wstring(messageText) << "\n";
        wcout << "Native Error : " << nativeError << "\n";
    }

    return result;
}

void ReadDatabase1(const wchar_t* connectionString) {

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

                        DBRow contactRow(statementHandle);
                        bool endOfData = false;

                        contactRow.AddColumn(new DBwstringColumn(L"FirstName", SQL_C_WCHAR, BUFFER_SIZE, 1));
                        contactRow.AddColumn(new DBwstringColumn(L"LastName", SQL_C_WCHAR, BUFFER_SIZE, 2));

                        std::wcout << contactRow.ColumnNames() << "\n";

                        while (!endOfData) {
                            status = SQLFetch(statementHandle);

                            if (status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO) {
                                std::wcout << contactRow.ColumnValues() << L"\n";
                            } else {
                                endOfData = true;

                                if (status != SQL_NO_DATA) {
                                    CheckSQLStatus("SQLFetch", status, statementHandle, SQL_HANDLE_STMT);
                                }
                            }
                        }

                        contactRow.DeleteColumns();
                    }
                }

                status = SQLDisconnect(connectionHandle);
            }

            SQLFreeHandle(SQL_HANDLE_DBC, connectionHandle);
        }
        SQLFreeHandle(SQL_HANDLE_ENV, envHandle);
    }
}

SQLRETURN ReadDatabase(wstring connectionString) {

    const int BUFFER_SIZE = 255;

    DBConnection connection;
    SQLRETURN status = SQL_SUCCESS;

    connection.ConnectionString(connectionString);

    if (connection.Connect()) {

        ContactTable contacts(&connection);

        contacts.DBTable::Read();

        status = connection.Disconnect();
    }
    else {
        status = connection.Status();
    }

    return status;
}