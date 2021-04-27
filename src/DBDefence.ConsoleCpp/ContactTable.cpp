#include <iostream>

#include "ContactTable.h"

ContactTable::ContactTable(DBConnection* connection)
    : DBTable(connection, wstring(L"Contact"), NULL) {

    const int BUFFER_SIZE = 255;

    _row->AddColumn(new DBColumn(L"FirstName", SQL_C_WCHAR, BUFFER_SIZE, 1));
    _row->AddColumn(new DBColumn(L"LastName", SQL_C_WCHAR, BUFFER_SIZE, 2));

    Statement(L"SELECT FirstName, LastName FROM Contact");
}

/// <summary>
/// Called for each row fetched.
/// </summary>
/// <param name="rowData"></param>
void
ContactTable::OutputRow() {
    wcout << _row->ColumnValues() << L"\n";
}