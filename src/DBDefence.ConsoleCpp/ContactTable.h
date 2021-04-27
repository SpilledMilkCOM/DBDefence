#pragma once

#include "DBTable.h"

class ContactTable : public DBTable {

public:

    ContactTable(DBConnection* connection);

    virtual void OutputRow();
};