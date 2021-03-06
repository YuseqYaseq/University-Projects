USE [jjasek_a]
GO
/****** Object:  Table [dbo].[CorporateCustomer]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CorporateCustomer](
	[CustomerID] [bigint] NOT NULL,
	[CompanyName] [nvarchar](500) NOT NULL,
	[RepresentativeName] [nvarchar](500) NULL,
UNIQUE NONCLUSTERED 
(
	[CustomerID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[CorporateCustomer]  WITH CHECK ADD  CONSTRAINT [CorporateCustomer_fk0] FOREIGN KEY([CustomerID])
REFERENCES [dbo].[Customer] ([CustomerID])
ON UPDATE CASCADE
GO
ALTER TABLE [dbo].[CorporateCustomer] CHECK CONSTRAINT [CorporateCustomer_fk0]
GO
