#include "DBwstringColumn.h"

using namespace std;

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBwstringColumn::DBwstringColumn(wstring name, int size, int columnNumber)
    : DBColumn(name, SQL_C_WCHAR, size, columnNumber) {

    _buffer = (SQLWCHAR*)malloc((_size + 1) * sizeof(SQLWCHAR));
    *_buffer = 0;
}

DBwstringColumn::DBwstringColumn(SQLHSTMT statementHandle, wstring name, int size, int columnNumber)
    : DBColumn(name, SQL_C_WCHAR, size, columnNumber) {

    Bind(statementHandle);
}

DBwstringColumn::~DBwstringColumn() {
    if (_buffer != NULL) {
        // TODO: MEMORY LEAK!!
        //free(_buffer);
        _buffer = NULL;
    }

    // TODO: DO I NEED TO FREE THE std string and wstring??
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

SQLRETURN
DBwstringColumn::Bind(SQLHSTMT statementHandle) {

    SQLLEN actualLength = 0;

    _status = SQLBindCol(statementHandle, _columnNumber, _type, _buffer, _size + 1, &actualLength);

    return _status;
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

wstring
DBwstringColumn::Value() {
    return wstring(_buffer);
}