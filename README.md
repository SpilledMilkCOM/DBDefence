# DBDefence <img src="https://s7.orientaltrading.com/is/image/OrientalTrading/PDP_VIEWER_IMAGE/d-fence-spirit-signs~13829802" height=50px />
*(note the "British" spelling of defense)*

## Create Test App & Database(s)
* Create default MVC C# project
* Create test database and table
* Create another test database and table with the **same schema**
* Create DB context for both databases
* Create web page to display both tables from each DB
  * Make sure the data is different in each DB
* Verify the app displays data from both databases

## Database Setup
* Add the Application Pool user to the server.
  * `IIS APPPOOL\DBDefenceAppPool`
* Add the user to the database(s)
  * Had to make user DBO because Entity Framework code was attempting to create a table.
  * Need to figure out how to turn that off.

## Encrypt Database

* Use DbDefence Database Encryptor
* Connect to SQLEXPRESS
* Select database to encrypt
* Enter a **super secret** password, I chose:
  * `SuperSecretPassword` which was not complex enough
  * `Id.Like.2.Encrypt_This!NOW!` which passed muster
* The Encryptor will not encrypt if there are any connects to the database.
  * Close all connections from SSMS
* Once encrypted you will get errors when attempting to open the database objects using SSMS
  * Any queries will fail unless access is given to it
    * `OPEN SYMMETRIC KEY DBDX DECRYPTION BY PASSWORD='Id.Like.2.Encrypt_This!NOW!'`
    * Any commands may now be run in the query window once access has been given.
    * `SELECT * FROM dbo.Contact`
    * You do not have to run the "open symmetric key..." command every time, it can actually
      be deleted from the query window to keep away from prying eyes. 👀

## Questions to ask DBDefence

* Can we install an already encrypted DB using a DAK pack?
* Can somebody impersonate an IIS APPPOOL user?
  * All a moot point if the authentication is done through their API
* 

## REF:

* [DBDefence](https://www.database-encryption.com/)
  * Also installed IIS module
  * Is free for databases up to 30 MB
* [Documentation](https://www.database-encryption.com/support/dbdefence-documentation/)