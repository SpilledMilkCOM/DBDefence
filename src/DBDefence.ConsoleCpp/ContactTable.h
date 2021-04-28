#pragma once

#include "DBTable.h"

/// <summary>
/// This class sets up a reader for the contact table.
/// </summary>
class ContactTable : public DBTable {

public:

    ContactTable(DBConnection* connection);

    virtual void OutputRow();
};