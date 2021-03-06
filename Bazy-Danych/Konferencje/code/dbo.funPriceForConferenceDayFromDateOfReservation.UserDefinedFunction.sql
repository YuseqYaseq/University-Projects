USE [jjasek_a]
GO
/****** Object:  UserDefinedFunction [dbo].[funPriceForConferenceDayFromDateOfReservation]    Script Date: 10.05.2018 10:52:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[funPriceForConferenceDayFromDateOfReservation]
(	
	@ConferenceDayID BigInt,
	@ReservationDate date
)
RETURNS Money 
AS
BEGIN
	RETURN 
	(
		SELECT TOP 1 CDP.Price FROM ConferenceDayPrice CDP
		WHERE CDP.ConferenceDayID = @ConferenceDayID AND @ReservationDate <= CDP.PriceDateLimit
		ORDER BY CDP.PriceDateLimit  
	)
END
GO
