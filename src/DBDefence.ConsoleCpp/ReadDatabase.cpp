#include <Windows.h>
//#include <sql.h>
#include <sqlext.h>

void ReadDatabase() {

    SQLHDBC connectionHandle;
    SQLHENV envHandle;
    SQLRETURN status;

    HWND desktopHandle = GetDesktopWindow();

    status = SQLAllocEnv(&envHandle);

    if (status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO) {

        status = SQLAllocConnect(envHandle, &connectionHandle);

        if (status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO) {

            //     <add name="DefaultConnection" providerName="System.Data.SqlClient" connectionString="Data Source=.\SQLEXPRESS;Initial Catalog=TestDB;Integrated Security=True;MultipleActiveResultSets=True" />

            SQLWCHAR* serverName = (SQLWCHAR*)L".\\SQLEXPRESS";
            const wchar_t* connectionString = L"Driver={ODBC Driver 11 for SQL Server}; Server=localhost\\SQLExpress; Initial Catalog=TestDB; Integrated Security=True; MultipleActiveResultSets=True";
            SQLWCHAR outConnStr[255];
            SQLSMALLINT outConnStrLen;

            //status = SQLConnect(connectionHandle, serverName, _countof(L".\SQLEXPRESS"), );

            // SQL_DRIVER_COMPLETE, SQL_DRIVER_NOPROMPT

            status = SQLDriverConnect(connectionHandle, desktopHandle, (SQLWCHAR*)connectionString, SQL_NTSL, outConnStr, 255, &outConnStrLen, SQL_DRIVER_COMPLETE);

            if (status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO) {

                SQLDisconnect(connectionHandle);
            }

            SQLFreeHandle(SQL_HANDLE_DBC, connectionHandle);
        }
        SQLFreeHandle(SQL_HANDLE_ENV, envHandle);
    }
}