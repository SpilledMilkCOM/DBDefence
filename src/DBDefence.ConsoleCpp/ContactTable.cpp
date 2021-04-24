#include <iostream>

#include "ContactTable.h"

ContactTable::ContactTable()
    : DBTable(wstring(L"Contact"), NULL) {
}

/// <summary>
/// Called for each row fetched.
/// </summary>
/// <param name="rowData"></param>
void
ContactTable::OutputRow() {
    wcout << _row->ColumnValues() << L"\n";
}