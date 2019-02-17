#ifndef _I2C_H_
#define	_I2C_H_

/************/
/* Module 1 */
/************/

/************************************************************
Function name:	i2c1Config
Description:	This function configures the I2C module and 
					sets the baud rate value is also 
					configured
Parameter:		fscl	- I2C clock frequency (KHz)
Return Value:	none
************************************************************/
void i2c1Config(unsigned int fscl);

/************************************************************
Function name:	i2c1Start
Description:	This routine generates Start condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Start(void);

/************************************************************
Function name:	i2c1Stop
Description:	This routine generates Stop condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Stop(void);

/************************************************************
Function name:	i2c1Restart
Description:	This routine generates Restart condition
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Restart(void);

/************************************************************
Function name:	i2c1DataReady
Description:	This routine provides the status whether the 
					receive buffer is full by returning the 
					RBF bit
Parameter:		none
Return Value:	RBF bit:  1 - data ready
						  0 - data not ready
************************************************************/
unsigned char i2c1DataRdy(void);

/************************************************************
Function name:	i2c1Idle
Description:	This routine generates wait condition until 
					I2C bus is Idle
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Idle(void);

/************************************************************
Function name:	i2c1Ack
Description:	This routine generates acknowledge condition 
					during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c1Ack(void);

/************************************************************
Function name:	i2c1NotAck
Description:	This routine generates not acknowledge 
					condition during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c1NotAck(void);

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
char i2c1Write(unsigned char data);

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
unsigned char i2c1Read(void);



/************/
/* Module 2 */
/************/

/************************************************************
Function name:	i2c2Config
Description:	This function configures the I2C module and 
					sets the baud rate value is also 
					configured
Parameter:		fscl	- I2C clock frequency (KHz)
Return Value:	none
************************************************************/
void i2c2Config(unsigned int fscl);

/************************************************************
Function name:	i2c2Start
Description:	This routine generates Start condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Start(void);

/************************************************************
Function name:	i2c2Stop
Description:	This routine generates Stop condition 
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Stop(void);

/************************************************************
Function name:	i2c2Restart
Description:	This routine generates Restart condition
					during master mode
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Restart(void);

/************************************************************
Function name:	i2c2DataReady
Description:	This routine provides the status whether the 
					receive buffer is full by returning the 
					RBF bit
Parameter:		none
Return Value:	RBF bit:  1 - data ready
						  0 - data not ready
************************************************************/
unsigned char i2c2DataRdy(void);

/************************************************************
Function name:	i2c2Idle
Description:	This routine generates wait condition until 
					I2C bus is Idle
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Idle(void);

/************************************************************
Function name:	i2c2Ack
Description:	This routine generates acknowledge condition 
					during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c2Ack(void);

/************************************************************
Function name:	i2c2NotAck
Description:	This routine generates not acknowledge 
					condition during master receive
Parameter:		none
Return Value:	none
************************************************************/
void i2c2NotAck(void);

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
char i2c2Write(unsigned char data);

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
unsigned char i2c2Read(void);

#endif
