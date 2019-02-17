#include <plib.h>
#include "i2c.h"
#include "HardwareProfile.h"

/************/
/* Module 1 */
/************/

/************************************************************
Function name:	i2c1Start
Description:	This routine generates Start condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Start(void)
{
	I2C_STATUS  status;
	
	// Wait for the bus to be idle, then start the transfer
	while( !I2CBusIsIdle(RTC_I2C_BUS) );
	
	// Wait for the signal to complete
	do
	{
		status = I2CGetStatus(RTC_I2C_BUS);
	
	} while ( !(status & I2C_START) );
}

/************************************************************
Function name:	i2c1Stop
Description:	This routine generates Stop condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Stop(void)
{
	//Initiate stop condition
    I2C1CONbits.PEN = 1;
	
	//Wait for stop condition to finish
	while (I2C1CONbits.PEN);
}

/************************************************************
Function name:	i2c1Restart
Description:	This routine generates Restart condition
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Restart(void)
{ 
	//Initiate restart condition
    I2C1CONbits.RSEN = 1;
	
	//Wait for restart condition to finish
	while (I2C1CONbits.RSEN);
}

/************************************************************
Function name:	i2c1DataReady
Description:	This routine provides the status whether the 
					receive buffer is full by returning the 
					RBF bit
Parameter:		none
Return Value:	RBF bit:  1 - data ready
						  0 - data not ready
************************************************************/
unsigned char i2c1DataRdy(void)
{
    return I2C1STATbits.RBF;
}

/************************************************************
Function name:	i2c1Idle
Description:	This routine generates wait condition until 
					I2C bus is Idle
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
          I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);	
}

/************************************************************
Function name:	i2c1Ack
Description:	This routine generates acknowledge condition 
					during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Ack(void)
{
	I2C1CONbits.ACKDT = 0;
	I2C1CONbits.ACKEN = 1;
}

/************************************************************
Function name:	i2c1NotAck
Description:	This routine generates not acknowledge 
					condition during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c1NotAck(void)
{
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1;
}

/************************************************************
Function name:	i2c1Write
Description:	This routine is used to write a byte to the 
					I2C bus. The input parameter data_out is 
					written to the I2CTRN register. If IWCOL 
					bit is set, write collision has occured 
					and -1 is returned, else 0 is returned.
Parameter:		data	- data to be written
Return Value:	char	- operation status
************************************************************/
char i2c1Write(unsigned char data)
{
	char rtr;
	
	while (I2C1STATbits.TBF);				// Wait till data is transmitted
	
    I2C1TRN = data;

    if(I2C1STATbits.IWCOL)        			// If write collision occurs,return -1
        rtr = -1;
    else
    {
        while(I2C1STATbits.TRSTAT);  		// wait until write cycle is complete 
			i2c1Idle();                		// ensure module is idle
			
        if (I2C1STATbits.ACKSTAT) 			// test for ACK condition received
			rtr = -2;
	    else 
			rtr = 0;	               		// if WCOL bit is not set return non-negative #
    }
	
	while(I2C1STATbits.TBF);             	// Wait till data is transmitted.	
	i2c1Idle();
	
	return (rtr);
}

/************************************************************
Function name:	i2c1Read
Description:	This routine reads a single byte from the I2C 
					Bus. To enable master receive, RCEN bit 
					is set. The RCEN bit is checked until it 
					is cleared. When cleared, the receive 
					register is full and it's contents are 
                    returned.
Parameter:		none
Return Value:	char	- data read
************************************************************/
unsigned char i2c1Read(void)
{
	unsigned char data;
	
	i2c1Idle();
	
    I2C1CONbits.RCEN = 1;					// Initiate Read condition
	
    while(I2C1CONbits.RCEN);				// Wait for Read condition to finish
	while(!I2C1STATbits.RBF);
	
	I2C1STATbits.I2COV = 0;

	data = I2C1RCV;
	
    return (data);
}



/************/
/* Module 2 */
/************/

/************************************************************
Function name:	i2c2Config
Description:	This function configures the I2C module and 
					sets the baud rate value
Parameter:		fscl	- I2C clock frequency (KHz)
Return Value:	none
************************************************************/
void i2c2Config(unsigned int fscl)
{
	//Configure I2C Baud Rate
	switch(fscl)
	{
		case 100:	I2C2BRG = 0x27;
					break;

		case 1000:	I2C2BRG = 0x03;
					break;	
		
		case 400:			
		default:	I2C2BRG = 0x09;
					break;	
	}
	
	//Enable I2C
	I2C2CONbits.I2CEN = 0;		
}

/************************************************************
Function name:	i2c2Start
Description:	This routine generates Start condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Start(void)
{
	//Initiate start condition
	I2C2CONbits.SEN = 1;			 
	
	//Wait for start condition to finish
	while(I2C2CONbits.SEN);		
}

/************************************************************
Function name:	i2c2Stop
Description:	This routine generates Stop condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Stop(void)
{
	//Initiate stop condition
    I2C2CONbits.PEN = 1;
	
	//Wait for stop condition to finish
	while(I2C2CONbits.PEN);
}

/************************************************************
Function name:	i2c2Restart
Description:	This routine generates Restart condition
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Restart(void)
{ 
	//Initiate restart condition
    I2C2CONbits.RSEN = 1;
	
	//Wait for restart condition to finish
	while(I2C2CONbits.RSEN);
}

/************************************************************
Function name:	i2c2DataReady
Description:	This routine provides the status whether the 
					receive buffer is full by returning the 
					RBF bit
Parameter:		none
Return Value:	RBF bit:  1 - data ready
						  0 - data not ready
************************************************************/
unsigned char i2c2DataRdy(void)
{
    return I2C2STATbits.RBF;
}

/************************************************************
Function name:	i2c2Idle
Description:	This routine generates wait condition until 
					I2C bus is Idle
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Idle(void)
{
    /* Wait until I2C Bus is Inactive */
    while(I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
          I2C2CONbits.RSEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);	
}

/************************************************************
Function name:	i2c2Ack
Description:	This routine generates acknowledge condition 
					during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Ack(void)
{
	I2C2CONbits.ACKDT = 0;
	I2C2CONbits.ACKEN = 1;
}

/************************************************************
Function name:	i2c2NotAck
Description:	This routine generates not acknowledge 
					condition during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c2NotAck(void)
{
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
}

/************************************************************
Function name:	i2c2Write
Description:	This routine is used to write a byte to the 
					I2C bus. The input parameter data_out is 
					written to the I2CTRN register. If IWCOL 
					bit is set, write collision has occured 
					and -1 is returned, else 0 is returned.
Parameter:		data	- data to be written
Return Value:	char	- operation status
************************************************************/
char i2c2Write(unsigned char data)
{
	char rtr;
	
	while (I2C2STATbits.TBF);				// Wait till data is transmitted
	
    I2C2TRN = data;

    if(I2C2STATbits.IWCOL)        			// If write collision occurs,return -1
        rtr = -1;
    else
    {
        while(I2C2STATbits.TRSTAT);  		// wait until write cycle is complete 
			i2c2Idle();                		// ensure module is idle
			
        if (I2C2STATbits.ACKSTAT) 			// test for ACK condition received
			rtr = -2;
	    else 
			rtr = 0;	               		// if WCOL bit is not set return non-negative #
    }
	
	while(I2C2STATbits.TBF);             	// Wait till data is transmitted.	
	
	i2c2Idle();
	
	return (rtr);
}

/************************************************************
Function name:	i2c1Read
Description:	This routine reads a single byte from the I2C 
					Bus. To enable master receive, RCEN bit 
					is set. The RCEN bit is checked until it 
					is cleared. When cleared, the receive 
					register is full and it's contents are 
                    returned.
Parameter:		none
Return Value:	char	- data read
************************************************************/
unsigned char i2c2Read(void)
{
	unsigned char data;
	
	i2c2Idle();
	
    I2C2CONbits.RCEN = 1;					// Initiate Read condition
	
    while(I2C2CONbits.RCEN);				// Wait for Read condition to finish
	while(!I2C2STATbits.RBF);

	I2C2STATbits.I2COV = 0;

	data = I2C2RCV;
	
    return (data);
}
