#include "DBRow.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBRow::DBRow() { }

DBRow::DBRow(SQLHSTMT statementHandle) {
    _statementHandle = statementHandle;
}

DBRow::~DBRow() {
    DeleteColumns();
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

void
DBRow::AddColumn(DBColumn* column) {
    _columns.push_back(column);

    if (_statementHandle != SQL_NULL_HSTMT) {
        column->Bind(_statementHandle);
    }
}

SQLRETURN
DBRow::Bind(SQLHSTMT statementHandle) {

    for (DBColumn* column : _columns) {
        _status = column->Bind(statementHandle);

        if (!(_status == SQL_SUCCESS || _status == SQL_SUCCESS_WITH_INFO)) {
            break;
        }
    }

    return _status;
}

std::wstring
DBRow::ColumnNames(std::wstring delimiter) {
    std::wstring result;

    for (DBColumn* column : _columns) {
        if (!result.empty()) {
            result += delimiter;
        }

        result += column->Name();
    }

    return result;
}

std::wstring
DBRow::ColumnValues(std::wstring delimiter) {
    std::wstring result;

    for (DBColumn* column : _columns) {
        if (!result.empty()) {
            result += delimiter;
        }

        result += column->Value();
    }

    return result;
}

void DBRow::DeleteColumns() {
    for (DBColumn* column : _columns) {
        delete(column);
    }
    _columns.clear();
}
