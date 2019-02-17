#ifndef _PWM_H_
#define	_PWM_H_

/************************************************************
Function name:	pwmInit
Description:	Initiate pwm
Parameter:		select duty-cycle, channel
Return Value:	none
************************************************************/
void pwmInit(void);

/************************************************************
Function name:	pwmDutyCycle
Description:	change next dutyCycle
Parameter:		channel
Return Value:	none
************************************************************/
void pwmDutyCycle(unsigned int dutyCycle, unsigned char channel);

/************************************************************
Function name:	ioAnalogOutput
Description:	outputs an analog voltage [0; 10.4]V
Parameter:		voltage, channel
Return Value:	none
************************************************************/
void ioAnalogOutput(float voltage, unsigned char channel);

#endif
