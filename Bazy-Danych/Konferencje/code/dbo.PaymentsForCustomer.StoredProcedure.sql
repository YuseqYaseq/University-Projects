USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[PaymentsForCustomer]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[PaymentsForCustomer](@CusID bigint)
AS BEGIN
	SELECT P.PaymentID, P.Title, P.Amount, P.SenderName, P.SenderAccountNumber, P.ReceivedDate
	FROM Customer C
	JOIN Reservation R ON R.CustomerID = C.CustomerID
	JOIN Payment P ON P.ReservationID = R.ReservationID
	WHERE C.CustomerID = @CusID
END
GO
