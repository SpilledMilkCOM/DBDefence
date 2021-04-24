#include "DBColumn.h"

using namespace std;

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBColumn::DBColumn(wstring name, int type, int size, int columnNumber) {

    if (name.empty()) {
        throw new exception("'name' cannot be empty.");
    }

    if (size < 1) {
        throw new exception("'size' must be greater or equal to 1.");
    }

    if (columnNumber < 1) {
        throw new exception("'columnNumber' must be greater or equal to 1.");
    }

    _name = name;
    _type = type;
    _size = size;
    _columnNumber = columnNumber;

    _buffer = (SQLWCHAR*)malloc((_size + 1) * sizeof(SQLWCHAR));
    *_buffer = 0;
}

DBColumn::DBColumn(SQLHSTMT statementHandle, wstring name, int type, int size, int columnNumber)
    : DBColumn(name, type, size, columnNumber) {

    Bind(statementHandle);
}

DBColumn::~DBColumn() {
    if (_buffer != NULL) {
        // TODO: MEMORY LEAK!!
        //free(_buffer);
        _buffer = NULL;
    }

    // TODO: DO I NEED TO FREE THE std string and wstring??
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

SQLRETURN
DBColumn::Bind(SQLHSTMT statementHandle) {

    SQLLEN actualLength = 0;

    _status = SQLBindCol(statementHandle, _columnNumber, _type, _buffer, _size + 1, &actualLength);

    return _status;
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

wstring
DBColumn::Name() {
    return _name;
}

SQLRETURN
DBColumn::Status() {
    return _status;
}

wstring
DBColumn::Value() {
    return wstring(_buffer);
}