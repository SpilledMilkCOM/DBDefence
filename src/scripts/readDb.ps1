$sqlCmd = "C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\170\Tools\Binn\sqlcmd.exe"
$dbName = "TestDB"
$query = "SELECT * FROM dbo.Contact"
$instance = "localhost\SQLExpress"
$openSymmetric = "OPEN SYMMETRIC KEY DBDX DECRYPTION BY PASSWORD='Id.Like.2.Encrypt_This!NOW!'"

. $sqlCmd -S $instance -E -d $dbName -Q $query

. $sqlCmd -S $instance -E -d "TestDBEncrypted" -Q "$openSymmetric; $query"