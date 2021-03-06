USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[ParticipantListForConference]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[ParticipantListForConference](@ConfID bigint)
AS BEGIN
	SELECT P.FirstName, P.LastName, A.BuildingNumber, A.StreetName, A.City, A.PostalCode, A.Region, A.Country, P.PhoneNumber, P.EmailAddress
	FROM Conference Con
	LEFT JOIN ConferenceDay CD ON CD.ConferenceID = Con.ConferenceID
	JOIN Event E ON E.EventID = CD.EventID
	LEFT JOIN ReservationList RL ON RL.EventID = E.EventID
	LEFT JOIN ReservationListDetails RLD ON RLD.ReservationListID = RL.ReservationListID
	JOIN Participant P ON P.ParticipantID = RLD.ParticipantID
	JOIN Address A ON A.AddressID = P.AddressID
	WHERE Con.ConferenceID = @ConfID
END
GO
