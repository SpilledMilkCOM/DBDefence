# src

### 📁 DBDefence.Console

* A C# console app that connects to a small contact database and reads the Contact table.
* Uses EntityFramework against a SQLExpress database.
* Calls **DbDefence DLL** to access an ecrypted database.

### 📁 DBDefence.ConsoleCPP

* A C++ console app that connects to a small contact database and reads the Contact table.
* Uses native SQL ODBC calls against a SQLExpress database.
* Abstracts native SQL calls into `DBTable`, `DBRow`, `DBColumn`, etc.
* Calls **DbDefence DLL** to access an ecrypted database.

### 📁 DBDefence

* A C# web app that connects to a small contact database and reads the Contact table.
* Uses EntityFramework against a SQLExpress database.
* Calls **DbDefence DLL** to access an ecrypted database.

### 📁 SQL
* Script to create the Contact table
* Script to populate the Contact table
* Script to extract data from Contact table