#ifndef _FRAM_H_
#define _FRAM_H_

#define FRAM_ENABLE		0
#define FRAM_DISABLE	1

/* FRAM Command Codes */
#define WRITE_ENABLE	0x06
#define WRITE_DISABLE	0x04
#define READ_STATUS		0x05
#define WRITE_STATUS	0x01
#define READ_DATA		0x03
#define WRITE_DATA		0x02
#define FRAM_SLEEP		0xB9
#define FRAM_WAKE		0xAB

/* Structures */
typedef union
{
	unsigned char reg;
	
	struct
	{
		unsigned reserved0	: 1;
		unsigned wel		: 1;
		unsigned bp0		: 1;
		unsigned bp1		: 1;
		unsigned reserved1	: 3;
		unsigned srwd		: 1;
	};
} FRAM;

/* FUNCTION PROTOTYPES */
/************************************************************
Function name:	framWake
Description:	wakes up FRAM from a sleep state
Parameter:		void
Return Value:	void
************************************************************/
void framWake(void);

/************************************************************
Function name:	framSleep
Description:	puts FRAM into a sleep state
Parameter:		void
Return Value:	void
************************************************************/
void framSleep(void);

/************************************************************
Function name:	framReadStatus
Description:	reads the status register of the FRAM
Parameter:		void
Return Value:	status register
************************************************************/
unsigned char framReadStatus(void);

/************************************************************
Function name:	framWriteStatus
Description:	writes into the status register of the FRAM
Parameter:		char to be written into the status register
Return Value:	void
************************************************************/
void framWriteStatus(unsigned char status);

/************************************************************
Function name:	framWriteEnable
Description:	enables writing to the FRAM
Parameter:		void
Return Value:	void
************************************************************/
void framWriteEnable(void);

/************************************************************
Function name:	framWriteDisable
Description:	disables writing to the FRAM
Parameter:		void
Return Value:	void
************************************************************/
void framWriteDisable(void);

/************************************************************
Function name:	framWriteData
Description:	writes data to the fram
Parameter:		startAdd - start address to start the writing
				buf - data buffer
				len - number of char to be written in successive positions
Return Value:	void
************************************************************/
void framWriteData(unsigned int startAdd, unsigned char * buf, unsigned char len);

/************************************************************
Function name:	framReadData
Description:	reads data from the fram
Parameter:		startAdd - start address to start the reading
				buf - data read
				len - number of char to be read from successive positions
Return Value:	void
************************************************************/
void framReadData(unsigned int startAdd, unsigned char * buf, unsigned char len);

void framHoldEnable(void);

void framHoldDisable(void);

void framWriteStatusDisable(void);

void framWriteStatusEnable(void);

#endif
