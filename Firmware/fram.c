#include <plib.h>
#include "fram.h"
#include "HardwareProfile.h"

FRAM fram;

unsigned int spiBuf[5];

/************************************************************
Function name:	framWake
Description:	wakes up FRAM from a sleep state
Parameter:		void
Return Value:	void
************************************************************/
void framWake(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, FRAM_WAKE);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

/************************************************************
Function name:	framSleep
Description:	puts FRAM into a sleep state
Parameter:		void
Return Value:	void
************************************************************/
void framSleep(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, FRAM_SLEEP);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

/************************************************************
Function name:	framReadStatus
Description:	reads the status register of the FRAM
Parameter:		void
Return Value:	status register
************************************************************/
unsigned char framReadStatus(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, READ_STATUS);
	fram.reg = SpiChnGetC(SPI_CHANNEL1);

	CS_FRAM = FRAM_DISABLE;
	
	printf("\nFRAM: \t%d\t%d\t%d\t%d\n", spiBuf[0], spiBuf[1], spiBuf[2], spiBuf[3]);
	
	return fram.reg;
}

/************************************************************
Function name:	framWriteStatus
Description:	writes into the status register of the FRAM
Parameter:		char to be written into the status register
Return Value:	void
************************************************************/
void framWriteStatus(unsigned char status)
{
	unsigned char dummySpi;
	
	framWriteStatusEnable();
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, WRITE_STATUS);
	SpiChnPutC(SPI_CHANNEL1, status);	
	
	CS_FRAM = FRAM_DISABLE;
	
	framWriteStatusDisable();
}

/************************************************************
Function name:	framWriteEnable
Description:	enables writing to the FRAM
Parameter:		void
Return Value:	void
************************************************************/
void framWriteEnable(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, WRITE_ENABLE);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

/************************************************************
Function name:	framWriteDisable
Description:	disables writing to the FRAM
Parameter:		void
Return Value:	void
************************************************************/
void framWriteDisable(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, WRITE_DISABLE);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

/************************************************************
Function name:	framWriteData
Description:	writes data to the fram
Parameter:		startAdd - start address to start the writing
				buf - data buffer
				len - number of char to be written in successive positions
Return Value:	void
************************************************************/
void framWriteData(unsigned int startAdd, unsigned char * buf, unsigned char len)
{
	unsigned char i;
	unsigned char dummySpi;
	
	framHoldEnable();
	framWriteEnable();
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, WRITE_DATA);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	SpiChnPutC(SPI_CHANNEL1, (unsigned char)(startAdd>>8));
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	SpiChnPutC(SPI_CHANNEL1, (unsigned char)(startAdd & 0x00FF));
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	for(i=0;i<len;i++)
	{
		SpiChnPutC(SPI_CHANNEL1, buf[i]);
		SpiChnGetC(SPI_CHANNEL1);		//clean buffer		
	}
	
	CS_FRAM = FRAM_DISABLE;
	
	framWriteDisable();
	framHoldDisable();
}

/************************************************************
Function name:	framReadData
Description:	reads data from the fram
Parameter:		startAdd - start address to start the reading
				buf - data read
				len - number of char to be read from successive positions
Return Value:	void
************************************************************/
void framReadData(unsigned int startAdd, unsigned char * buf, unsigned char len)
{
	unsigned char i;
	unsigned char dummySpi;
	
	framHoldEnable();
	
	CS_FRAM = FRAM_ENABLE;
	
	SpiChnPutC(SPI_CHANNEL1, READ_DATA);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	SpiChnPutC(SPI_CHANNEL1, (unsigned char)(startAdd>>8));
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	SpiChnPutC(SPI_CHANNEL1, (unsigned char)(startAdd & 0x00FF));
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
		
	for(i=0;i<len;i++)
	{
		SpiChnPutC(SPI_CHANNEL1, 0x00);
		buf[i] = SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	}
	
	CS_FRAM = FRAM_DISABLE;
	
	framHoldDisable();
}

void framHoldEnable(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	HOLD = 1;

	SpiChnPutC(SPI_CHANNEL1, 0x00);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

void framHoldDisable(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	HOLD = 0;

	SpiChnPutC(SPI_CHANNEL1, 0x00);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

void framWriteStatusDisable(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	WP1 = 1;

	SpiChnPutC(SPI_CHANNEL1, 0x00);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}

void framWriteStatusEnable(void)
{
	unsigned char dummySpi;
	
	CS_FRAM = FRAM_ENABLE;
	
	WP1 = 0;

	SpiChnPutC(SPI_CHANNEL1, 0x00);
	SpiChnGetC(SPI_CHANNEL1);		//clean buffer
	
	CS_FRAM = FRAM_DISABLE;
}
