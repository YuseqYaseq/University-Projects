USE [jjasek_a]
GO
/****** Object:  Table [dbo].[ReservationListDetails]    Script Date: 10.05.2018 10:52:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ReservationListDetails](
	[ReservationListID] [bigint] NOT NULL,
	[ParticipantID] [bigint] NOT NULL,
	[ReservationType] [nvarchar](50) NOT NULL
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[ReservationListDetails]  WITH CHECK ADD  CONSTRAINT [ReservationListDetails_fk0] FOREIGN KEY([ReservationListID])
REFERENCES [dbo].[ReservationList] ([ReservationListID])
ON UPDATE CASCADE
GO
ALTER TABLE [dbo].[ReservationListDetails] CHECK CONSTRAINT [ReservationListDetails_fk0]
GO
ALTER TABLE [dbo].[ReservationListDetails]  WITH CHECK ADD  CONSTRAINT [ReservationListDetails_fk1] FOREIGN KEY([ParticipantID])
REFERENCES [dbo].[Participant] ([ParticipantID])
GO
ALTER TABLE [dbo].[ReservationListDetails] CHECK CONSTRAINT [ReservationListDetails_fk1]
GO
ALTER TABLE [dbo].[ReservationListDetails]  WITH CHECK ADD  CONSTRAINT [CK_ReservationListDetails] CHECK  (([ReservationType]='Normal' OR [ReservationType]='Student'))
GO
ALTER TABLE [dbo].[ReservationListDetails] CHECK CONSTRAINT [CK_ReservationListDetails]
GO
