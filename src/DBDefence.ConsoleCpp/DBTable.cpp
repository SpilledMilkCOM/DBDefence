#include "DBTable.h"

// TODO: Change name to DBDataReader

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

DBTable::DBTable(DBConnection* connection) {

    _connection = connection;

    _row = new DBRow();

    _allocatedDefault = true;
    _sqlUtil = new SQLUtil(NULL);
}

DBTable::DBTable(DBConnection* connection, wstring tableName, SQLUtil* sqlUtil) {

    _connection = connection;

    _row = new DBRow();

    _tableName = tableName;

    if (sqlUtil == NULL) {
        _allocatedDefault = true;
        _sqlUtil = new SQLUtil(NULL);
    } else {
        _sqlUtil = sqlUtil;
    }
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

//----==== PROPERTIES ====-------------------------------------------------------------------------

wstring
DBTable::Statement() {
    return (_statement == NULL) ? wstring() : _statement->Statement();
}

wstring
DBTable::Statement(wstring statement) {
    wstring previousStatement = Statement();

    if (_statement != NULL) {
        delete(_statement);
        _statement = NULL;
    }

    _statement = new DBStatement(statement, _connection, _row, _sqlUtil);

    return previousStatement;
}

//----==== PUBLIC ====-----------------------------------------------------------------------------

void
DBTable::Read() {
    if (_statement != NULL) {
        while (_statement->Fetch()) {
            OutputRow();
        }
    }
}