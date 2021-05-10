#include "DBColumn.h"

using namespace std;

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBColumn::DBColumn(wstring name, int type, int size, int columnNumber) {

    if (name.empty()) {
        throw exception("'name' cannot be empty.");
    }

    if (size < 1) {
        throw exception("'size' must be greater or equal to 1.");
    }

    if (columnNumber < 1) {
        throw exception("'columnNumber' must be greater or equal to 1.");
    }

    _name = name;
    _type = type;
    _size = size;
    _columnNumber = columnNumber;
}

DBColumn::DBColumn(SQLHSTMT statementHandle, wstring name, int type, int size, int columnNumber)
    : DBColumn(name, type, size, columnNumber) {

    Bind(statementHandle);
}

DBColumn::~DBColumn() {
    // TODO: DO I NEED TO FREE THE std string and wstring??
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

SQLRETURN
DBColumn::Bind(SQLHSTMT statementHandle) {
    throw exception("NOT IMPLEMENTED");
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