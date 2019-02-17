#include <plib.h>
#include "HardwareProfile.h"
#include "io.h"

static unsigned int srValue = 0;

/************************************************************
Function name:	ioOutputCtrl
Description:	control outputs
Parameter:		nPort	- select port
				ctrl	- turn on/off
Return Value:	none
************************************************************/
void ioOutputCtrl(unsigned int nPort, unsigned char ctrl)
{
	switch(nPort)
	{
		case 1:  OUT1  = ctrl;break;	
		case 2:  OUT2  = ctrl;break;	
		case 3:  OUT3  = ctrl;break;
		case 4:  OUT4  = ctrl;break;	
		case 5:  OUT5  = ctrl;break;	
		case 6:  OUT6  = ctrl;break;	
		case 7:  OUT7  = ctrl;break;
		case 8:  OUT8  = ctrl;break;		
		case 9:  OUT9  = ctrl;break;
		case 10: OUT10 = ctrl;break;
		case 11: OUT11 = ctrl;break;
		case 12: OUT12 = ctrl;break;
		case 13: OUT13 = ctrl;break;
		case 14: OUT14 = ctrl;break;	
		case 15: OUT15 = ctrl;break;		
		case 16: OUT16 = ctrl;break;		
		case ALL:	OUT1 = ctrl;
					OUT2 = ctrl;
					OUT3 = ctrl;
					OUT4 = ctrl;
					OUT5 = ctrl;
					OUT6 = ctrl;
					OUT7 = ctrl;
					OUT8 = ctrl;
					OUT9 = ctrl;
					OUT10 = ctrl;
					OUT11 = ctrl;
					OUT12 = ctrl;
					OUT13 = ctrl;
					OUT14 = ctrl;	
					OUT15 = ctrl;
					OUT16 = ctrl;
					break;	
		default: break;				
	}
}

/************************************************************
Function name:	ioInputStatus
Description:	read input port status
Parameter:		channel to read
Return Value:	0,1
ERROR Value:	2, if bad channel selection
************************************************************/
unsigned char ioInputStatus(unsigned char channel)
{
	if(channel==13){S3=1;Nop();S2=1;Nop();S1=1;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel==14){S3=1;Nop();S2=1;Nop();S1=1;Nop();S0=0;Nop();Delayms(1);return E1;}	
	if(channel==15){S3=1;Nop();S2=1;Nop();S1=0;Nop();S0=1;Nop();Delayms(1);return E1;}	
	if(channel==16){S3=1;Nop();S2=1;Nop();S1=0;Nop();S0=0;Nop();Delayms(1);return E1;}	
	if(channel==12){S3=1;Nop();S2=0;Nop();S1=1;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel==11){S3=1;Nop();S2=0;Nop();S1=1;Nop();S0=0;Nop();Delayms(1);return E1;}
	if(channel==10){S3=1;Nop();S2=0;Nop();S1=0;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel== 9){S3=1;Nop();S2=0;Nop();S1=0;Nop();S0=0;Nop();Delayms(1);return E1;}
	if(channel== 8){S3=0;Nop();S2=1;Nop();S1=1;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel== 7){S3=0;Nop();S2=1;Nop();S1=1;Nop();S0=0;Nop();Delayms(1);return E1;}
	if(channel== 6){S3=0;Nop();S2=1;Nop();S1=0;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel== 5){S3=0;Nop();S2=1;Nop();S1=0;Nop();S0=0;Nop();Delayms(1);return E1;}
	if(channel== 4){S3=0;Nop();S2=0;Nop();S1=1;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel== 3){S3=0;Nop();S2=0;Nop();S1=1;Nop();S0=0;Nop();Delayms(1);return E1;}
	if(channel== 2){S3=0;Nop();S2=0;Nop();S1=0;Nop();S0=1;Nop();Delayms(1);return E1;}
	if(channel== 1){S3=0;Nop();S2=0;Nop();S1=0;Nop();S0=0;Nop();Delayms(1);return E1;}
	return 2;
}

/******************************/
/*     TOGGLING SYSTEM LED    */
/******************************/
void systemLedToggle(void)
{
	static BOOL statusLed = 0;
	
	statusLed = !statusLed;
	LD_SYS = statusLed;
}
