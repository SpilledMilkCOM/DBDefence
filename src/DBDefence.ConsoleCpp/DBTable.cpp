#include "DBTable.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBTable::DBTable() {

    _row = new DBRow();

    _allocatedDefault = true;
    _sqlUtil = new SQLUtil(NULL);
}

DBTable::DBTable(wstring tableName, SQLUtil* sqlUtil) {

    _row = new DBRow();

    _tableName = tableName;
    _sqlUtil = sqlUtil;
}

DBTable::~DBTable() {

    if (_row != NULL) {
        delete(_row);
        _row = NULL;
    }

    if (_allocatedDefault && _sqlUtil != NULL) {
        delete(_sqlUtil);
    }
    _sqlUtil = NULL;
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

void
DBTable::Read() {
    // Fetch all of the rows from the select statement.

    bool endOfData = false;

    while (!endOfData) {
        _status = SQLFetch(_statementHandle);

        if (_status == SQL_SUCCESS || _status == SQL_SUCCESS_WITH_INFO) {
            OutputRow();
        } else {
            endOfData = true;

            if (_status != SQL_NO_DATA) {
                _sqlUtil->CheckSQLStatus("SQLFetch", _status, _statementHandle, SQL_HANDLE_STMT);
            }
        }
    }
}