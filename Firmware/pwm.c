#include <plib.h>
#include "HardwareProfile.h"
#include "pwm.h"

#define PRESCALE		1
#define T2_TICK 		(GetPeripheralClock()/PRESCALE/4)
				
/************************************************************
Function name:	pwmInit
Description:	Initiate pwm
Parameter:		select duty-cycle, channel
Return Value:	none
************************************************************/
void pwmInit(void)
{
	/*OpenTimer2(T2_ON, 0x3FF);
	OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC |  OC_PWM_FAULT_PIN_DISABLE  | OC_LOW_HIGH , 0x3FF, 0x00 );
	OpenTimer3(T3_ON, 0x3FF);
	OpenOC3( OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC |  OC_PWM_FAULT_PIN_DISABLE  | OC_LOW_HIGH , 0x3FF, 0x00 );
	*/
	OpenTimer2(T2_ON, 0x3FF);
	OpenOC2( OC_ON | OC_TIMER2_SRC |  OC_PWM_FAULT_PIN_DISABLE  ,0,0);
	OpenTimer3(T3_ON, 0x3FF);
	OpenOC3( OC_ON | OC_TIMER3_SRC |  OC_PWM_FAULT_PIN_DISABLE  ,0,0);
}

/************************************************************
Function name:	pwmDutyCycle
Description:	change next dutyCycle
Parameter:		duty cycle , channel
Return Value:	none
************************************************************/
void pwmDutyCycle(unsigned int dutyCycle, unsigned char channel)
{
	if(channel==1)
	{
		OC3RS =dutyCycle;
	}
	if(channel==2)
	{
		OC2RS =dutyCycle;
	}
}

/************************************************************
Function name:	ioAnalogOutput
Description:	change AnalogOutput Voltage
Parameter:		float voltage, channel
Return Value:	none
************************************************************/
void ioAnalogOutput(float voltage, unsigned char channel)
{
	float aux;
	unsigned int dutyCycle;
	if(voltage>10.4)voltage=10.4;
	if(voltage<0)voltage=0;
	aux=voltage/10.4;
	dutyCycle=1023*aux;
	
	if(channel==1)
	{
		OC3RS =dutyCycle;
	}
	if(channel==2)
	{
		OC2RS =dutyCycle;
	}
}
