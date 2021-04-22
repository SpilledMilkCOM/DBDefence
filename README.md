# <img src="https://s7.orientaltrading.com/is/image/OrientalTrading/PDP_VIEWER_IMAGE/d-fence-spirit-signs~13829802" height=50px /> DBDefence 
*(note the **British** spelling of defense)*

This project is a proof of concept to proove out the use of [DbDefence](https://www.database-encryption.com/)
to encrypt a database.  My theory was to start with an small app that just reads a single table
from an **un**encrypted database.  Once that worked I created an identical database that was still
**not** encrypted and verified that a second page could access that data from a different
connection/context.  After reading some of the encryption documentation, I set up an IIS site
that points to a locally published directory and allow that application pool to be configured
with the **DbDefence Configuration Tool** that will associate the password with the App Pool
user.  Then encrypted second database fired up the site.  After a few errors I ended up having
to do section 3.0, but let's say this worked flawlessly the **first** time.

## 1.0 🏗️ Create Test App & Database(s)

* *(The following in 1.0 has been included in this project except for the database creation.  Or
you can follow these steps to build it on your own.)*
* Create default MVC C# project
* Create DB context for both databases *(since their schema will be shared)*
* Create web page to display table from un-encrypted DB
* Create web page to display table from the DB that **will** be encrypted
  * Make sure the data is different in each DB
* Create test database and table
  * 📁 Look in the src/SQL folder for the table creation scripts
* Create another test database and table with the **same schema**
* ▶️ Verify the app displays data from both databases using the debugger and IIS Express
* Publish the website locally to a folder

## 2.0 🌐 IIS Setup

* Create a website in IIS and point the site to the published folder above.
  * Make sure you use a unique port
* Create another website (use a "Debug" suffix) in IIS and point it to the DBDefence project folder
  `src/DBDefence`
  * Make sure you use a unique port *(possibly increment or decrement the previous port if you
    think the debug site comes before or after the published site)*
* Make sure that you use the same Application Pool for both so the encryption password will be
  used for both sites.

## 3.0 🧰 Database Setup

* Add the Application Pool user to the server. *(possibly SQLExpress - which is what I used)*
  * `IIS APPPOOL\DBDefenceAppPool`
* Add the user to the database(s)
  * Had to make user DBO because Entity Framework code was attempting to create a table.
  * Need to figure out how to turn that off.

## 4.0 🔐 Encrypt Database

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

## 5.0 ⚙️ Configure DbDefence Application Pool

* Run the configuration tool and select the App Pool that is running the sites
* Enter the encrypted database name and password and click save.
* Restart the Application Pool

## 6.0 🏃‍ Running

* Use IIS to launch the non debug site and you should see both tables' data
* In order to debug:
  * Configure the project to launch Local IIS under the Web tab on the project's property tab.
  * Make sure you reference by `http://localhost:[debug port you assigned]`
  * ▶️ Verify this will run within Visual Studio and that you can set breakpoints.
* You can always launch the debug website and then attach to the w3wp.exe process, but make sure
  you select the correct App Pool user.
  * Once attached, you will be able to break at breakpoints.

## ❔ Questions to ask DBDefence support

* Can we install an already encrypted DB using a DAK pack?
* Can somebody impersonate an IIS APPPOOL user?
  * All a moot point if the authentication is done through their API.

## 📚 REF:

* [DBDefence](https://www.database-encryption.com/)
  * Also installed IIS module
  * Is free for databases up to 30 MB
* [Documentation](https://www.database-encryption.com/support/dbdefence-documentation/)
* [MS Understanding Identities](https://docs.microsoft.com/en-us/troubleshoot/iis/understanding-identities)
  * Has a good section on impersonation.