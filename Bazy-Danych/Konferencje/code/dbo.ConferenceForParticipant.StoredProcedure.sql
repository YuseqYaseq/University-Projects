USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[ConferenceForParticipant]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[ConferenceForParticipant](@ParID bigint)
AS BEGIN
	SELECT C.Title, C.Description
	FROM Participant P
	LEFT JOIN ReservationListDetails RLD ON RLD.ParticipantID = P.ParticipantID
	JOIN ReservationList RL ON RL.ReservationListID = RLD.ReservationListID
	JOIN Event E ON E.EventID = RL.EventID
	JOIN ConferenceDay CD ON CD.EventID = E.EventID
	JOIN Conference C ON C.ConferenceID = CD.ConferenceID
	WHERE P.ParticipantID = @ParID
END
GO
