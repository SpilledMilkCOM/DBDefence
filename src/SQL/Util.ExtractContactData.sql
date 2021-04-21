
SELECT
		'INSERT INTO Contact ([FirstName],[LastName],[Password],[Email],[Phone]) VALUES ('
		+ '''' + [FirstName] + ''','
		+ '''' + [LastName] + ''','
		+ '''' + TRIM([Password]) + ''','
		+ '''' + [Email] + ''','
		+ '''' + [Phone] + ''')'
  FROM [dbo].[Contact]