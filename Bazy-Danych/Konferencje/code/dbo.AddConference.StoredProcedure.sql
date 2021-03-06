USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[AddConference]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AddConference](
	@Title		nvarchar(255),
	@Desc		nvarchar(1000),
	@BegTime	date,
	@EndTime	date,
	@DDiscount	real,
	@DAddress	bigint,
	@DAvailableSeats bigint)
AS BEGIN
	INSERT INTO Conference(Title, Description)
	VALUES(@Title, @Desc);
	DECLARE @i int
	DECLARE @all int
	DECLARE @confID bigint
	SET @confID = SCOPE_IDENTITY()
	SET @i = DATEDIFF(d, @BegTime, @EndTime)
	SET @all = @i
	WHILE (@i >= 0)
	BEGIN
		INSERT INTO Event(Title, Description, AddressID, AvailableSeats)
		VALUES(@Title + ': day no. ' + CAST((@all - @i) as nvarchar), @Desc, @DAddress, @DAvailableSeats);
		INSERT INTO ConferenceDay(EventID, ConferenceID, Date, StudentDiscount)
		VALUES(SCOPE_IDENTITY(), @confID, DATEADD(d, @all - @i, @BegTime), @DDiscount)
		SET @i = @i - 1
	END
END
GO
