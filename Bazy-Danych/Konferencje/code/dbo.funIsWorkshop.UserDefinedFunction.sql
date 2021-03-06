USE [jjasek_a]
GO
/****** Object:  UserDefinedFunction [dbo].[funIsWorkshop]    Script Date: 10.05.2018 10:52:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date, ,>
-- Description:	<Description, ,>
-- =============================================
CREATE FUNCTION [dbo].[funIsWorkshop]
(
	-- Add the parameters for the function here
	@EventID BigInt
)
RETURNS Bit
AS
BEGIN
	-- Declare the return variable here
	IF EXISTS(SELECT * FROM Workshop W WHERE W.EventID = @EventID)
		RETURN 1
	RETURN 0
END
GO
