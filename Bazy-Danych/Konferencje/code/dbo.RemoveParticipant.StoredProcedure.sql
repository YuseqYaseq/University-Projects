USE [jjasek_a]
GO
/****** Object:  StoredProcedure [dbo].[RemoveParticipant]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[RemoveParticipant](
	@ParticipantID bigint)
AS BEGIN
	DELETE FROM Participant WHERE @ParticipantID = ParticipantID
END
GO
