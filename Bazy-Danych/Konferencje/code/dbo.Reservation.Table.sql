USE [jjasek_a]
GO
/****** Object:  Table [dbo].[Reservation]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Reservation](
	[ReservationID] [bigint] IDENTITY(1,1) NOT NULL,
	[CustomerID] [bigint] NOT NULL,
	[PurchaseDate] [datetime2](7) NOT NULL,
	[CancelDate] [datetime2](7) NULL,
	[ReservationStatus] [nvarchar](255) NOT NULL,
	[ClientNote] [nvarchar](1000) NULL,
 CONSTRAINT [PK_RESERVATION] PRIMARY KEY CLUSTERED 
(
	[ReservationID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Index [IX_Reservation]    Script Date: 10.05.2018 10:52:20 ******/
CREATE NONCLUSTERED INDEX [IX_Reservation] ON [dbo].[Reservation]
(
	[PurchaseDate] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Reservation]  WITH CHECK ADD  CONSTRAINT [Reservation_fk0] FOREIGN KEY([CustomerID])
REFERENCES [dbo].[Customer] ([CustomerID])
ON UPDATE CASCADE
GO
ALTER TABLE [dbo].[Reservation] CHECK CONSTRAINT [Reservation_fk0]
GO
ALTER TABLE [dbo].[Reservation]  WITH CHECK ADD  CONSTRAINT [CK_Dates] CHECK  (([PurchaseDate]<[CancelDate]))
GO
ALTER TABLE [dbo].[Reservation] CHECK CONSTRAINT [CK_Dates]
GO
ALTER TABLE [dbo].[Reservation]  WITH CHECK ADD  CONSTRAINT [CK_ReservationEnum] CHECK  (([ReservationStatus]='Canceled' OR [ReservationStatus]='Paid' OR [ReservationStatus]='Reserved'))
GO
ALTER TABLE [dbo].[Reservation] CHECK CONSTRAINT [CK_ReservationEnum]
GO
