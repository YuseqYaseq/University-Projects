USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[EventsForParticipant]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[EventsForParticipant](@ParID bigint)
AS BEGIN
	SELECT E.Title, E.Description, A.BuildingNumber, A.StreetName, A.City, A.PostalCode, A.Country, A.Region
	FROM Participant P
	LEFT JOIN ReservationListDetails RLD ON RLD.ParticipantID = P.ParticipantID
	JOIN ReservationList RL ON RL.ReservationListID = RLD.ReservationListID
	JOIN Event E ON E.EventID = RL.EventID
	JOIN Address A ON E.AddressID = A.AddressID
	WHERE P.ParticipantID = @ParID
END
GO
