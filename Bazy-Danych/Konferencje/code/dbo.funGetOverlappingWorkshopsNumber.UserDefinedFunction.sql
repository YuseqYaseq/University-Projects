USE [jjasek_a]
GO
/****** Object:  UserDefinedFunction [dbo].[funGetOverlappingWorkshopsNumber]    Script Date: 10.05.2018 10:52:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date, ,>
-- Description:	<Description, ,>
-- =============================================
CREATE FUNCTION [dbo].[funGetOverlappingWorkshopsNumber]
(
	-- Add the parameters for the function here
	@ParticipantID BigInt
)
RETURNS BigInt
AS
BEGIN
	-- Declare the return variable here
	DECLARE @OverlappingWorkshops BigInt
	-- Add the T-SQL statements to compute the return value here
	SET @OverlappingWorkshops = (SELECT COUNT(WL1.EventID)
	FROM  dbo.tabFunGetAttendedWorkshopsList(1) WL1
	CROSS JOIN dbo.tabFunGetAttendedWorkshopsList(1) WL2
	WHERE dbo.funGetEventDate(WL1.EventID) = dbo.funGetEventDate(WL2.EventID)  AND
	(WL1.BeginTime BETWEEN WL2.BeginTime AND WL2.EndTime OR WL1.EndTime BETWEEN WL2.BeginTime AND WL2.EndTime))
	
	RETURN @OverlappingWorkshops
END
GO
