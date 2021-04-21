USE TestDB

INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('Parker','Smart','ThisShouldBeEncrypted','parker.smart@gmail.com','3035551211')
INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('John','Doe','password','john.doe@gmail.com','3035551212')

USE TestDBEncrypted

INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('Bruce','Wayne','adseife13$#@1zxhgr','bruce.wayne@gmail.com','3035551211')
INSERT INTO dbo.Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('The','Joker','hahahahahaha','joker@gmail.com','3035551212')
