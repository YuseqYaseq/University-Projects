USE [jjasek_a]
GO
/****** Object:  View [dbo].[AllCustomersWithAddresses]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[AllCustomersWithAddresses] AS
SELECT CompanyName + ISNULL(' represented by ' + RepresentativeName, ' (no representative)')  AS Name, PhoneNumber, EmailAddress,
BuildingNumber, StreetName, City, PostalCode, Region, Country, Notes
FROM dbo.CorporateCustomersWithAddress
UNION
SELECT FirstName + ' ' + LastName, PhoneNumber, EmailAddress,
BuildingNumber, StreetName, City, PostalCode, Region, Country, Notes
FROM dbo.RetailCustomersWithAddresses
GO
