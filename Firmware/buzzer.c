#include "buzzer.h"
#include "Compiler.h"
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"

/************************************************************
Function name:	buzzerCtrl
Description:	control buzzer
Parameter:		ctrl	- turn the buzzer on/off
Return Value:	none
************************************************************/
void buzzerCtrl(unsigned char ctrl)
{
	BUZZER = ctrl;
}
