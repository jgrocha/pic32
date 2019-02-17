#include <plib.h>
#include "matrixKeyboard.h"
#include "HardwareProfile.h"
#include <Compiler.h>

#define HIGH	1
#define LOW		0

/************************************************************
Function name:	keyboardRead
Description:	
Parameter:		
Return Value:	none
************************************************************/
unsigned char keyboardRead(void)
{
	unsigned char val = 0;

	KB_X3=1;Nop();Nop();
	KB_X2=1;Nop();Nop();
	KB_X1=1;Nop();Nop();
	KB_X0=1;Nop();Nop();
	KB_X0 = 0;Nop();Nop();
	Delayms(1);
	 	 if(KB_Y0 == 0 && KB_Y1==1 && KB_Y2==1 && KB_Y3==1)val = 8;
	else if(KB_Y0 == 1 && KB_Y1==0 && KB_Y2==1 && KB_Y3==1)val = 4;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==0 && KB_Y3==1)val = 3;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==1 && KB_Y3==0)val = 6;
	
	KB_X3=1;Nop();Nop();
	KB_X2=1;Nop();Nop();
	KB_X1=1;Nop();Nop();
	KB_X0=1;Nop();Nop();
	KB_X1 = 0;Nop();Nop();
	Delayms(1);
	 	 //if(KB_Y0 == 0 && KB_Y1==1 && KB_Y2==1 && KB_Y3==1)val = 11; else
	if(KB_Y0 == 1 && KB_Y1==0 && KB_Y2==1 && KB_Y3==1)val = 1;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==0 && KB_Y3==1)val = 2;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==1 && KB_Y3==0)val = 3;

	KB_X3=1;Nop();Nop();
	KB_X2=1;Nop();Nop();
	KB_X1=1;Nop();Nop();
	KB_X0=1;Nop();Nop();
	KB_X2 = 0;Nop();Nop();
	Delayms(1);
	 	 if(KB_Y0 == 0 && KB_Y1==1 && KB_Y2==1 && KB_Y3==1)val = 9;
	//else if(KB_Y0 == 1 && KB_Y1==0 && KB_Y2==1 && KB_Y3==1)val = 14;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==0 && KB_Y3==1)val = 1;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==1 && KB_Y3==0)val = 4;
	
	KB_X3=1;Nop();Nop();
	KB_X2=1;Nop();Nop();
	KB_X1=1;Nop();Nop();
	KB_X0=1;Nop();Nop();
	KB_X3 = 0;Nop();Nop();
	Delayms(1);
	 	 if(KB_Y0 == 0 && KB_Y1==1 && KB_Y2==1 && KB_Y3==1)val = 7;
	//else if(KB_Y0 == 1 && KB_Y1==0 && KB_Y2==1 && KB_Y3==1)val = 9;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==0 && KB_Y3==1)val = 2;
	else if(KB_Y0 == 1 && KB_Y1==1 && KB_Y2==1 && KB_Y3==0)val = 5;
	
	KB_X3=1;Nop();Nop();
	KB_X2=1;Nop();Nop();
	KB_X1=1;Nop();Nop();
	KB_X0=1;Nop();Nop();
	return val;
}	