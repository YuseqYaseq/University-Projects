USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[RemoveCustomer]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[RemoveCustomer](
	@CustomerID bigint)
AS BEGIN
	DECLARE @date date
	SET @date = GETDATE()
	DECLARE @I bigint
	DECLARE cur CURSOR LOCAL FOR
			SELECT ReservationID
			FROM Reservation
			WHERE CustomerID = @CustomerID
	OPEN cur;
	FETCH NEXT FROM cur INTO @I;
	WHILE @@FETCH_STATUS=0
	BEGIN
		EXEC [dbo].CancelReservation  @I, @date
		FETCH NEXT FROM cur INTO @I;
	END
	CLOSE cur;
	DEALLOCATE cur;
	DELETE FROM ClientTaxpayerDetails WHERE CustomerID=@CustomerID
	DELETE FROM CorporateCustomer WHERE CustomerID=@CustomerID
	DELETE FROM RetailCustomer WHERE CustomerID=@CustomerID
	DELETE FROM Customer WHERE CustomerID=@CustomerID
END
GO
