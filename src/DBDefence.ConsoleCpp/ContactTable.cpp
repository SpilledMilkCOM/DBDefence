#include <iostream>

#include "ContactTable.h"
#include "DBwstringColumn.h"

/// <summary>
/// Sets up the columns and statement for the Contact table.
/// </summary>
/// <param name="connection">Database connection</param>
ContactTable::ContactTable(DBConnection* connection)
    : DBTable(connection, wstring(L"Contact"), NULL) {

    const int BUFFER_SIZE = 255;

    _row->AddColumn(new DBwstringColumn(L"FirstName", BUFFER_SIZE, 1));
    _row->AddColumn(new DBwstringColumn(L"LastName", BUFFER_SIZE, 2));

    Statement(L"SELECT FirstName, LastName FROM dbo.Contact");
}

/// <summary>
/// Called for each row fetched.
/// </summary>
/// <param name="rowData"></param>
void
ContactTable::OutputRow() {
    wcout << _row->ColumnValues() << endl;
}