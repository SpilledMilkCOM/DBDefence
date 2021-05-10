#include "DBintColumn.h"

using namespace std;

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBintColumn::DBintColumn(wstring name, int columnNumber)
    : DBColumn(name, SQL_C_LONG, sizeof(_value), columnNumber) {
}

DBintColumn::DBintColumn(SQLHSTMT statementHandle, wstring name, int columnNumber)
    : DBColumn(name, SQL_C_LONG, sizeof(_value), columnNumber) {

    Bind(statementHandle);
}

DBintColumn::~DBintColumn() {
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

SQLRETURN
DBintColumn::Bind(SQLHSTMT statementHandle) {

    SQLLEN actualLength = 0;

    _status = SQLBindCol(statementHandle, _columnNumber, _type, &_value, _size, &actualLength);

    return _status;
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

wstring
DBintColumn::Value() {
    return to_wstring(_value);
}