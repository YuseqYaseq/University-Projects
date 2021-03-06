USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[RemoveOverdueReservations]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RemoveOverdueReservations]
AS BEGIN
	DECLARE @I bigint
	DECLARE @Date date
	SET @Date = GETDATE()
	DECLARE cur CURSOR LOCAL FOR
		SELECT ReservationID
		FROM Reservation
		WHERE ReservationStatus = 'Reserved' AND DATEDIFF(d, PurchaseDate, GETDATE()) > 7
	OPEN cur;
	FETCH NEXT FROM cur INTO @I;
	WHILE @@FETCH_STATUS=0
	BEGIN
		EXEC [dbo].[CancelReservation] @I, @Date
		FETCH NEXT FROM cur INTO @I;
	END
	CLOSE cur;
	DEALLOCATE cur;
END
GO
