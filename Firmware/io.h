#ifndef _IO_H_
#define _IO_H_

#define ALL		0

/***********************/
/* Function Prototypes */
/***********************/
/************************************************************
Function name:	ioOutputCtrl
Description:	control outputs
Parameter:		nPort	- select port
				ctrl	- turn on/off
Return Value:	none
************************************************************/
void ioOutputCtrl(unsigned int nPort, unsigned char ctrl);

/************************************************************
Function name:	ioInputStatus
Description:	read input port status
Parameter:		channel to read
Return Value:	0,1
ERROR Value:	2, if bad channel selection
************************************************************/
unsigned char ioInputStatus(unsigned char channel);

/******************************/
/*     TOGGLING SYSTEM LED    */
/******************************/
void systemLedToggle(void);

#endif
