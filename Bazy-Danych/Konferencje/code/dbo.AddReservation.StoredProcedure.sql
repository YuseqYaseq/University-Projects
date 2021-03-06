USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[AddReservation]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AddReservation](
	@CustomerID bigint,
	@PurchaseDate datetime2,
	@ClientNote nvarchar(1000),
	@EventID	bigint,
	@ReservedNormalSeats bigint,
	@ReservedStudentSeats bigint)
AS BEGIN
	BEGIN TRANSACTION
		ALTER TABLE Reservation DISABLE TRIGGER trg_Res_I_CheckIfReservationNotEmpty
		INSERT INTO Reservation(CustomerID, PurchaseDate, CancelDate, ReservationStatus, ClientNote)
		VALUES (@CustomerID, @PurchaseDate, NULL, 'Reserved', @ClientNote)

		DECLARE @Key bigint
		SET @Key = SCOPE_IDENTITY()
		IF NOT EXISTS(SELECT ReservationStatus FROM Reservation WHERE ReservationID=@Key AND ReservationStatus='Canceled')
		BEGIN
			INSERT INTO ReservationList VALUES(@Key, @EventID, @ReservedNormalSeats, @ReservedStudentSeats) 
			ALTER TABLE Reservation ENABLE TRIGGER trg_Res_I_CheckIfReservationNotEmpty
		END
	COMMIT;
END
GO
