#include <plib.h>
#include "HardwareProfile.h"
#include "rtc.h"
#include "uart.h"

RTC rtc;
TIME time;
DATE date;

/*******************************************************************************
  Function:
    BOOL StartTransfer( BOOL restart )

  Summary:
    Starts (or restarts) a transfer to/from the EEPROM.

  Description:
    This routine starts (or restarts) a transfer to/from the EEPROM, waiting (in
    a blocking loop) until the start (or re-start) condition has completed.

  Precondition:
    The I2C module must have been initialized.

  Parameters:
    restart - If FALSE, send a "Start" condition
            - If TRUE, send a "Restart" condition
    
  Returns:
    TRUE    - If successful
    FALSE   - If a collision occured during Start signaling
    
  Example:
    <code>
    StartTransfer(FALSE);
    </code>

  Remarks:
    This is a blocking routine that waits for the bus to be idle and the Start
    (or Restart) signal to complete.
  *****************************************************************************/
BOOL StartTransfer( BOOL restart )
{
    I2C_STATUS  status;

    // Send the Start (or Restart) signal
    if(restart)
    {
        I2CRepeatStart(RTC_I2C_BUS);
    }
    else
    {
        // Wait for the bus to be idle, then start the transfer
        while( !I2CBusIsIdle(RTC_I2C_BUS) );

        if(I2CStart(RTC_I2C_BUS) != I2C_SUCCESS)
        {
            return FALSE;
        }
    }

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(RTC_I2C_BUS);

    } while ( !(status & I2C_START) );

    return TRUE;
}


/*******************************************************************************
  Function:
    BOOL TransmitOneByte( UINT8 data )

  Summary:
    This transmits one byte to the EEPROM.

  Description:
    This transmits one byte to the EEPROM, and reports errors for any bus
    collisions.

  Precondition:
    The transfer must have been previously started.

  Parameters:
    data    - Data byte to transmit

  Returns:
    TRUE    - Data was sent successfully
    FALSE   - A bus collision occured

  Example:
    <code>
    TransmitOneByte(0xAA);
    </code>

  Remarks:
    This is a blocking routine that waits for the transmission to complete.
  *****************************************************************************/
BOOL TransmitOneByte( UINT8 data )
{
    // Wait for the transmitter to be ready
    while(!I2CTransmitterIsReady(RTC_I2C_BUS));

    // Transmit the byte
    if(I2CSendByte(RTC_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION)
    {
        return FALSE;
    }

    // Wait for the transmission to finish
    while(!I2CTransmissionHasCompleted(RTC_I2C_BUS));

    return TRUE;
}

/*******************************************************************************
  Function:
    void StopTransfer( void )

  Summary:
    Stops a transfer to/from the EEPROM.

  Description:
    This routine Stops a transfer to/from the EEPROM, waiting (in a 
    blocking loop) until the Stop condition has completed.

  Precondition:
    The I2C module must have been initialized & a transfer started.

  Parameters:
    None.
    
  Returns:
    None.
    
  Example:
    <code>
    StopTransfer();
    </code>

  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
  *****************************************************************************/
void StopTransfer( void )
{
    I2C_STATUS  status;

    // Send the Stop signal
    I2CStop(RTC_I2C_BUS);

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(RTC_I2C_BUS);

    } while ( !(status & I2C_STOP) );
}

/************************************************************
Function name:	rtcConfig
Description:	rtc configuration
Parameter:		none
Return Value:	none
************************************************************/
void rtcConfig(void)
{
	INT_RTC_TRIS = 1;
	
	// Set the I2C baudrate
	I2CSetFrequency(RTC_I2C_BUS, GetPeripheralClock(), I2C_CLOCK_FREQ);

    // Enable the I2C bus
    I2CEnable(RTC_I2C_BUS, TRUE);
	
	ConfigINT1(EXT_INT_ENABLE | FALLING_EDGE_INT | EXT_INT_PRI_2);
    INTClearFlag(INT_INT1);
    INTEnable(INT_INT1, INT_ENABLED);
    
	//Interrupt
	rtcWriteReg(A1SEC_ADDR,0x00);
	rtcWriteReg(A1MIN_ADDR, 0x00);
	rtcWriteReg(A1HOUR_ADDR, 0x00);
	rtcWriteReg(A1DAY_ADDR, 0x00);
	rtcWriteReg(A2MIN_ADDR, 0x00);
	rtcWriteReg(A2HOUR_ADDR, 0x00);
	rtcWriteReg(A2DAY_ADDR, 0x00);
	
	//Configure control register
		//enable oscillator
	rtcWriteReg(CONTROL_ADDR, 0x06);
	
	//Configure status register
	rtcWriteReg(STATUS_ADDR, 0x00);
	
	//Configure trickle charge register
	rtcWriteReg(TRICKLE_ADDR, 0x00);
}

/************************************************************
Function name:	rtcRead
Description:	read time from RTC (seconds, minutes, hour, 
					day, date, month, year)
Parameter:		none
Return Value:	none
************************************************************/
void rtcRead(void)
{	
	rtc.seconds.reg = rtcReadReg(SECONDS_ADDR);
	rtc.minutes.reg = rtcReadReg(MINUTES_ADDR);
	rtc.hours.reg = rtcReadReg(HOURS_ADDR);
	rtc.dayOfWeek.reg = rtcReadReg(DAYOFWEEK_ADDR);
	rtc.day.reg = rtcReadReg(DAY_ADDR);
	rtc.month.reg = rtcReadReg(MONTH_ADDR);
	rtc.year.reg = rtcReadReg(YEAR_ADDR);
	
	time.seconds = (rtc.seconds.seconds10*10) + rtc.seconds.seconds;
	time.minutes = (rtc.minutes.minutes10*10) + rtc.minutes.minutes;
	time.hours = (rtc.hours.hour10*10) + rtc.hours.hour;
	
	date.dayOfWeek = rtc.dayOfWeek.day;
	date.day = rtc.day.day10 + rtc.day.day;
	date.month = rtc.month.month10*10 + rtc.month.month;
	date.year = rtc.year.year10*10 + rtc.year.year + 2000;
}

/***************************************************************
Function name	: rtcUpdate
Description		: update rtc time
Parameters		: hour, minute, second, day, date, month, year
Return Value	: none
***************************************************************/
void rtcUpdate(unsigned char hour, unsigned char minute, unsigned char second, unsigned char day, unsigned char date, unsigned char month, unsigned char year)
{
	unsigned char temp;
	
	//Calculate Hour
	temp = (((hour/10)<<4) & 0x30) | (hour%10);
	rtcWriteReg(HOURS_ADDR, temp);
	
	//Calculate Minutes
	temp = ((minute/10)<<4) | (minute%10);
	rtcWriteReg(MINUTES_ADDR, temp);
	
	//Calculate Seconds
	temp = ((second/10)<<4) | (second%10);
	rtcWriteReg(SECONDS_ADDR, temp);	
	
	//Calculate Day of week
	rtcWriteReg(DAYOFWEEK_ADDR, day);
	
	//Calculate Day
	temp = ((date/10)<<4) | (date%10);
	rtcWriteReg(DAY_ADDR, temp);
	
	//Calculate Month
	temp = ((month/10)<<4) | (month%10);
	rtcWriteReg(MONTH_ADDR, temp);
	
	//Calculate Year
	temp = ((year/10)<<4) | (year%10);	
	rtcWriteReg(YEAR_ADDR, temp);
}

/************************************************************
Function name:	rtcWriteReg
Description:	write data to rtc register addrMem
Parameter:		addrMem - rtc register address
				data	- data to be written
Return Value:	none
************************************************************/
void rtcWriteReg(unsigned char addrMem, unsigned char data)
{
	UINT8               i2cData[10];
    int                 Index;
    int                 DataSz;
    UINT32              actualClock;
    BOOL                Acknowledged;
    BOOL                Success = TRUE;
    UINT8               i2cbyte;
	
    
	// Initialize the data buffer
	i2cData[0] = RTC_ADDR_W;
	i2cData[1] = addrMem;           // RTC location to read (high address byte)
	i2cData[2] = data;              // RTC location to read (low address byte)
	DataSz = 3;
	
	// Start the transfer to write data to the EEPROM
	
	while( !StartTransfer(FALSE) );
	
	// Transmit all data
	Index = 0;
	while( Success && (Index < DataSz) )
	{
		// Transmit a byte
		if (TransmitOneByte(i2cData[Index]))
		{
			// Advance to the next byte
			Index++;
			
			// Verify that the byte was acknowledged
			if(!I2CByteWasAcknowledged(RTC_I2C_BUS))
			{
				Success = FALSE;
			}
		}
		else
		{
			Success = FALSE;
		}
	}
	
	// End the transfer (hang here if an error occured)
	StopTransfer();

	while(!Success);
}

/************************************************************
Function name:	rtcReadReg
Description:	read data from rtc register addrMem
Parameter:		addrMem - rtc register address
Return Value:	unsigned char - data read
************************************************************/
unsigned char rtcReadReg(unsigned char addrMem)
{
	UINT8               i2cData[10];
    int                 Index;
    int                 DataSz;
    UINT32              actualClock;
    BOOL                Acknowledged;
    BOOL                Success = TRUE;
    UINT8               i2cbyte;
	unsigned char str[20];
   // Initialize the data buffer
    i2cData[0] = RTC_ADDR_W;
    i2cData[1] = addrMem;                           
    DataSz = 2;
    // Start the transfer to read the RTC
	
	//GLCD_GoTo(31,5);sprintf(str,"R1");GLCD_WriteString(str,1);

	while( !StartTransfer(FALSE) );/*if( !StartTransfer(FALSE) ) { while(1);}*/
	//Delayms(1);
	//GLCD_GoTo(31,5);sprintf(str,"R2");GLCD_WriteString(str,1);

    // Address the RTC.
    Index = 0;
    while( Success & (Index < DataSz) )
    {
        if (TransmitOneByte(i2cData[Index]))// Transmit a byte
        {
            Index++;// Advance to the next byte
        }
        else
        {
            Success = FALSE;
        }
        if(!I2CByteWasAcknowledged(RTC_I2C_BUS))// Verify that the byte was acknowledged
        {
            Success = FALSE;
        }
    }
    // Restart and send the RTC's internal address to switch to a read transfer
    if(Success)
    {
        // Send a Repeated Started condition
		//GLCD_GoTo(31,5);sprintf(str,"R3");GLCD_WriteString(str,1);
        while( !StartTransfer(TRUE) );/*if( !StartTransfer(TRUE) ){while(1);}*/
		//GLCD_GoTo(31,5);sprintf(str,"R4");GLCD_WriteString(str,1);
        // Transmit the address with the READ bit set
        if (TransmitOneByte(RTC_ADDR_R))
        {
            // Verify that the byte was acknowledged
            if(!I2CByteWasAcknowledged(RTC_I2C_BUS))
            {
                Success = FALSE;
            }
        }
        else
        {
            Success = FALSE;
        }
    }
    // Read the data from the desired address
    if(Success)
    {
        if(I2CReceiverEnable(RTC_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
        {
            Success = FALSE;
        }
        else
        {
		//GLCD_GoTo(31,5);sprintf(str,"R5");GLCD_WriteString(str,1);
            while(!I2CReceivedDataIsAvailable(RTC_I2C_BUS));
		//GLCD_GoTo(31,5);sprintf(str,"R6");GLCD_WriteString(str,1);
            i2cbyte = I2CGetByte(RTC_I2C_BUS);
        }
    }
    // End the transfer (stop here if an error occured)
    StopTransfer();
    while(!Success);
	return i2cbyte;
}

/************************************************************
Function name:	rtcClearAlarmFlag
Description:	clear alarm flag
Parameter:		alarmFlag - select which alarm flag to clear
Return Value:	none
************************************************************/
void rtcClearAlarmFlag(unsigned char alarmFlag)
{
	switch(alarmFlag)
	{
		case 1:	rtc.status.a1if = 0;
				rtcWriteReg(STATUS_ADDR, rtc.status.reg);	
				break;
				
		case 2: rtc.status.a2if = 0;
				rtcWriteReg(STATUS_ADDR, rtc.status.reg);	
				break;
				
		default: break;					
	}
}

/************************************************************
Function name:	rtcCheckValidity
Description:	check number of days of a month
Parameter:		m	- month
				y	- year
Return Value:	number of days of a month
************************************************************/
unsigned char rtcCheckValidity(unsigned char m, unsigned char y)
{
	unsigned d;
	unsigned int y1 = 2000 + y;
  
	if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
		d=31;
	else if(m==4 || m==6 || m==9 || m==11)
		d=30;
	else if((y1%100!=0 && y1%4==0) || y1%400==0)
		d=29;
	else
		d=28;
		 
	return d;
}

void rtcPrintTimeDate(void)
{
#ifdef DEBUG_RTC
	printf("\n************************************************************************");	
	printf("\nDate: %d%d-%d%d-%d%d\nTime: %d%d:%d%d:%d%d", rtc.day.day10, rtc.day.day,\
										rtc.month.month10, rtc.month.month,\
										rtc.year.year10, rtc.year.year,\
										rtc.hours.hour10, rtc.hours.hour,\
										rtc.minutes.minutes10, rtc.minutes.minutes,\
										rtc.seconds.seconds10, rtc.seconds.seconds);
	printf("\n************************************************************************\n\r");
#endif
}


