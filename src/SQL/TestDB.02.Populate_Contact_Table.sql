USE TestDB

DELETE FROM dbo.Contact

INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone],[NetWorth],[Rank]) VALUES ('Parker','Smart','ThisShouldBeEncrypted','parker.smart@gmail.com','3035551211', 10000000000.0, 100)
INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone],[NetWorth],[Rank]) VALUES ('John','Doe','password','john.doe@gmail.com','3035551212', 1111.11, 100)

USE TestDBEncrypted

INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('Bruce','Wayne','adseife13$#@1zxhgr','bruce.wayne@gmail.com','3035551211')
INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('The','Joker','hahahahahaha','joker@gmail.com','3035551212')
