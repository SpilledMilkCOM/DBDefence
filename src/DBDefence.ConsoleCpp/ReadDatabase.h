#pragma once

#include <Windows.h>
#include <sqlext.h>         // MUST include Windows.h above

SQLRETURN ReadDatabase(const wchar_t* connectionString);
void ReadDatabase2(const wchar_t* connectionString);