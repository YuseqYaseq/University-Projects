USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[AddParticipant]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AddParticipant](
	@FirstName nvarchar(255),
	@LastName nvarchar(255),
	@AddressID bigint,
	@PhoneNumber nvarchar(50),
	@Email varchar(320))
AS BEGIN
	INSERT INTO Participant(FirstName, LastName, AddressID, PhoneNumber, EmailAddress)
	VALUES (@FirstName, @LastName, @AddressID, @PhoneNumber, @Email);
END
GO
