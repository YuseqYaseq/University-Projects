USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[RemoveReservationList]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RemoveReservationList](
	@ReservationListID bigint)
AS BEGIN
	DECLARE @I bigint
	DECLARE cur CURSOR LOCAL FOR
		SELECT ParticipantID
		FROM ReservationListDetails
		WHERE ReservationListID=@ReservationListID
	OPEN cur;
	FETCH NEXT FROM cur INTO @I;
	WHILE @@FETCH_STATUS=0
	BEGIN
		EXEC [dbo].[RemoveParticipantFromList] @ReservationListID, @I
		FETCH NEXT FROM cur INTO @I;
	END
	CLOSE cur;
	DEALLOCATE cur;
	DELETE FROM ReservationList WHERE ReservationListID = @ReservationListID
END
GO
