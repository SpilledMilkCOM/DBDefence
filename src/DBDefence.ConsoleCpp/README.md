# DbDefence.ConsoleCpp

An executable that will connect to an encrypted database and dump out some data. This could be hard-coded
or possibly take SQL statement (which might be too open).

* Please pay attention to the platform!
  * Make sure the platform is set to x64 if using the 64-bit DLLs.


## 🤞 TODO
  
* Encapsulate the command line parsing
* 🏗️ Encapsulate the Database connection and table *(in progress)*

## ✨ DONE

* ✅ Execute raw SQL to obtain a connection and data from a table.
* ✅ Encapsulated database row and column

## 📚 REF:

* [DbDefence Command Line Encryptor](https://www.database-encryption.com/support/dbdefence-documentation/using-cmdline.html)
* [DbDefence Client](https://www.database-encryption.com/support/dbdefence-documentation/bclient.html)
* [Reading Password Characters](https://stackoverflow.com/questions/1413445/reading-a-password-from-stdcin)
* [SetConsoleMode](https://docs.microsoft.com/en-us/windows/console/setconsolemode)
* [LoadLibrary function](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)
* [GetProcAddress function](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)
* [SQLDriverConnect Function](https://docs.microsoft.com/en-us/sql/odbc/reference/syntax/sqldriverconnect-function?view=sql-server-ver15)
  * [ODBC Connection String Options](https://docs.microsoft.com/en-us/dotnet/api/system.data.odbc.odbcconnection.connectionstring?view=dotnet-plat-ext-5.0)
* [String Literal](https://en.cppreference.com/w/cpp/language/string_literal)
  * `L"This is a wide character string"`
  * `LR"(C:\raw\path\to\file.txt)"`
* [malloc/free vs new/delete](https://www.geeksforgeeks.org/new-vs-malloc-and-free-vs-delete-in-c/)
  * new/delete calls constructor/destructor, malloc/free does not.
* [ASCII Characters](https://www.asciihex.com/)