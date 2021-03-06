USE [jjasek_a]
GO
/****** Object:  UserDefinedFunction [dbo].[funRemainingPayForCustomer]    Script Date: 10.05.2018 10:52:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[funRemainingPayForCustomer](@CusID bigint)
RETURNS money
AS BEGIN
	DECLARE @ret money
	SET @ret =	(SELECT SUM(C.Amount)
				FROM dbo.CustomersWithPayments C
				WHERE C.CustomerID = @CusID
				GROUP BY C.CustomerID)
	RETURN ISNULL(@ret, 0)
END
GO
