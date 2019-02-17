#include <plib.h>
#include "HardwareProfile.h"
#include "spi.h"
#include "thermocouple.h"

/** Module ADS118 *******************************************/
/************************************************************
Function name:	WriteSPI(unsigned int config, int mode)
Description:	write SPI to transmit the configuration parameter for ADS11118, and receive the convertion result.
Parameters: 	config: configuration parameter of ADS11118's register, mode (0/1): internal temperature sensor, far-end temperature
Return value: 	ADC result
************************************************************/
static double tc1measures[10]; 
static double tc2measures[10]; 
static int firsttime1 = 0; 
static int firsttime2 = 0;

int thermocouple_writeSpi (unsigned int config, int mode){
	int msb1, msb2, msb;
	unsigned int temp;
	char dummy, dummy1, dummy2;
    int rdata;

	temp=config;

	//SPI Definitions for thermocouple ADS1118 module
	OpenSPI1(FRAME_ENABLE_OFF | ENABLE_SDO_PIN | SPI_MODE8_ON | SPI_SMP_ON | SPI_CKE_OFF | SLAVE_ENABLE_OFF \
				| CLK_POL_ACTIVE_HIGH | MASTER_ENABLE_ON | SEC_PRESCAL_8_1 | PRI_PRESCAL_64_1, \
					SPI_ENABLE | SPI_IDLE_STOP);

	if (mode == 1)
		temp = config | 0x8000;

	SpiChnPutC(SPI_CHANNEL1, temp >> 8); 
	msb1 = SpiChnGetC(SPI_CHANNEL1);
   	
	SpiChnPutC(SPI_CHANNEL1, temp & 0xFF); 

	msb2 = SpiChnGetC(SPI_CHANNEL1);
	msb = (msb1 << 8) | msb2;

	SpiChnPutC(SPI_CHANNEL1, temp >> 8); 

	dummy1 = SpiChnGetC(SPI_CHANNEL1);

	SpiChnPutC(SPI_CHANNEL1, temp & 0xFF); 

	dummy2 = SpiChnGetC(SPI_CHANNEL1);

	dummy = (dummy1 << 8) | dummy2;

	//Return to default SPI definitions
	//Definitions for all devices except Thermocouple readings
	OpenSPI1(FRAME_ENABLE_OFF | ENABLE_SDO_PIN | SPI_MODE8_ON | SPI_SMP_OFF | SPI_CKE_ON | SLAVE_ENABLE_OFF \
				| CLK_POL_ACTIVE_HIGH | MASTER_ENABLE_ON | SEC_PRESCAL_8_1 | PRI_PRESCAL_64_1, \
				SPI_ENABLE | SPI_IDLE_STOP);
	
	return msb; 
	
}


/******************************************************************************
 * function: ADSread(unsigned int mode)
 * introduction: read the ADC result and tart a new conversion.
 * parameters:
 * mode = 0, ADS1118 is set to convert the voltage of integrated temperature sensor.
 * mode = 1, ADS1118 is set to convert the voltage of thermocouple.
 * return value:result of last conversion
 ******************************************************************************/

int thermocouple_ADSread(unsigned int mode, unsigned int channel){
	unsigned int temp;
	int result;

	if(channel == 2)
	{
		if(mode == 1)
			temp = ADSCON_CH1;
		else
			temp = ADSCON_CH1 + ADS1118_TS;
	}
	else
	{
		
		if (mode==1)		// Set the configuration to AIN0/AIN1, FS=+/-0.256, SS, DR=128sps, PULLUP on DOUT
			temp = ADSCON_CH0;
		else
			temp = ADSCON_CH0 + ADS1118_TS;// temperature sensor mode.DR=8sps, PULLUP on DOUT
	}

	TMP2CS = TC_ENABLE;

	Delayms(10);
	result = thermocouple_writeSpi(temp, 1); 
	Delayms(10);

	TMP2CS = TC_DISABLE;

	return result; 

}

/******************************************************************************
 * function: localCompensation(int local_code)
 * introduction:
 * this function transform internal temperature sensor code to compensation code, which is added to thermocouple code.
 * local_data is at the first 14bits of the 16bits data register.
 * So we let the result data to be divided by 4 to replace right shifting 2 bits
 * for internal temperature sensor, 32 LSBs is equal to 1 Celsius Degree.
 * We use local_code/4 to transform local data to n* 1/32 degree.
 * the local temperature is transformed to compensation code for thermocouple directly.
 *                                                   (Tin -T[n-1])
 * comp codes = Code[n-1] + (Code[n] - Code[n-1])* {---------------}
 *													(T[n] - T[n-1])
 * for example: 5-10 degree the equation is as below
 *
 * tmp = (0x001A*(local_temp - 5))/5 + 0x0019;
 *
 * 0x0019 is the 'Code[n-1]' for 5 Degrees; 	0x001A = (Code[n] - Code[n-1])
 * (local_temp - 5) is (Tin -T[n-1]);			denominator '5' is (T[n] - T[n-1])
 *
 * the compensation range of local temperature is 0-125.
 * parameters: local_code, internal sensor result
 * return value: compensation codes
 ******************************************************************************/

int thermocouple_localCompensation(int local_code){
	float tmp,local_temp;
	int comp;
	local_code = local_code / 4;
	local_temp = (float)local_code / 32;	//

	if (local_temp >=0 && local_temp <=5)		//0~5
	{
		tmp = (0x0019*local_temp)/5;
		comp = tmp;
	}
	else if (local_temp> 5 && local_temp <=10)	//5~10
	{
		tmp = (0x001A*(local_temp - 5))/5 + 0x0019 ;
		comp = tmp;
	}
	else if (local_temp> 10 && local_temp <=20)	//10~20
	{
		tmp = (0x0033*(local_temp - 10))/10 + 0x0033 ;
		comp = tmp;
	}
	else if (local_temp> 20 && local_temp <=30)	//20~30
	{
		tmp = (0x0034*(local_temp - 20))/10 + 0x0066 ;
		comp = tmp;
	}
	else if (local_temp> 30 && local_temp <=40)	//30~40
	{
		tmp = (0x0034*(local_temp - 30))/10 + 0x009A ;
		comp = tmp;
	}
	else if (local_temp> 40 && local_temp <=50)	//40~50
	{
		tmp = (0x0035*(local_temp - 40))/10 + 0x00CE;
		comp = tmp;
	}

	else if (local_temp> 50 && local_temp <=60)	//50~60
	{
		tmp = (0x0035*(local_temp - 50))/10 + 0x0103;
		comp = tmp;
	}
	else if (local_temp> 60 && local_temp <=80)	//60~80
	{
		tmp = (0x006A*(local_temp - 60))/20 + 0x0138;
		comp = tmp;
	}
	else if (local_temp> 80 && local_temp <=125)//80~125
	{
		tmp = (0x00EE*(local_temp - 80))/45 + 0x01A2;
		comp = tmp;
	}
	else
	{
		comp = 0;
	}
	return comp;

}

/******************************************************************************
 * function: ADCcode2temp(int code)
 * introduction:
 * this function is used to convert ADC result codes to temperature.
 * converted temperature range is 0 to 500 Celsius degree
 * Omega Engineering Inc. Type K thermocouple is used, seebeck coefficient is about 40uV/Degree from 0 to 1000 degree.
 * ADC input range is +/-256mV. 16bits. so 1 LSB = 7.8125uV. the coefficient of code to temperature is 1 degree = 40/7.8125 LSBs.
 * Because of nonlinearity of thermocouple. Different coefficients are used in different temperature ranges.
 * the voltage codes is transformed to temperature as below equation
 * 							      (Codes - Code[n-1])
 * T = T[n-1] + (T[n]-T[n-1]) * {---------------------}
 * 							     (Code[n] - Code[n-1])
 *
 * parameters: code
 * return value: far-end temperature
*******************************************************************************/

int thermocouple_ADCcode2temp(int code){
	float temp;
	int t;

	temp = (float)code;

	if (code > 0xFF6C && code <=0xFFB5)			//-30~-15
	{
		temp = (float)(15 * (temp - 0xFF6C)) / 0x0049 - 30.0f;
	}
	else if (code > 0xFFB5 && code <=0xFFFF)	//-15~0
	{
		temp = (float)(15 * (temp - 0xFFB5)) / 0x004B - 15.0f;
	}
	else if (code >=0 && code <=0x0019)			//0~5
	{
		temp = (float)(5 * (temp - 0)) / 0x0019;
	}
	else if (code >0x0019 && code <=0x0033)		//5~10
	{
		temp = (float)(5 * (temp - 0x0019)) / 0x001A + 5.0f;
	}
	else if (code >0x0033 && code <=0x0066)		//10~20
	{
		temp = (float)(10 * (temp - 0x0033)) / 0x0033 + 10.0f;
	}
	else if (code > 0x0066 && code <= 0x009A)	//20~30
	{
		temp = (float)(10 * (temp - 0x0066)) / 0x0034 + 20.0f;
	}
	else if (code > 0x009A && code <= 0x00CE)	//30~40
	{
		temp = (float)(10 * (temp - 0x009A)) / 0x0034 + 30.0f;
	}
	else if ( code > 0x00CE && code <= 0x0103)	//40~50
	{
		temp = (float)(10 * (temp - 0x00CE)) / 0x0035 + 40.0f;
	}
	else if ( code > 0x0103 && code <= 0x0138)	//50~60
	{
		temp = (float)(10 * (temp - 0x0103)) / 0x0035 + 50.0f;
	}
	else if (code > 0x0138 && code <=0x01A2)	//60~80
	{
		temp = (float)(20 * (temp - 0x0138)) / 0x006A + 60.0f;
	}
	else if (code > 0x01A2 && code <= 0x020C)	//80~100
	{
		temp = (float)((temp - 0x01A2) * 20)/ 0x06A + 80.0f;
	}
	else if (code > 0x020C && code <= 0x02DE)	//100~140
	{
		temp = (float)((temp - 0x020C) * 40)/ 0x0D2 + 100.0f;
	}
	else if (code > 0x02DE && code <= 0x03AC)	//140~180
	{
		temp = (float)((temp - 0x02DE) * 40)/ 0x00CE + 140.0f;
	}
	else if (code > 0x03AC && code <= 0x0478)	//180~220
	{
		temp = (float)((temp - 0x03AB) * 40) / 0x00CD + 180.0f;
	}
	else if (code > 0x0478 && code <= 0x0548)	//220~260
	{
		temp = (float)((temp - 0x0478) * 40) / 0x00D0 + 220.0f;
	}
	else if (code > 0x0548 && code <= 0x061B)	//260~300
	{
		temp = (float)((temp - 0x0548) * 40) / 0x00D3 + 260.0f;
	}
	else if (code > 0x061B && code <= 0x06F2)	//300~340
	{
		temp = (float)((temp - 0x061B) * 40) /  0x00D7 + 300.0f;
	}
	else if (code > 0x06F2 && code <= 0x07C7)	//340~400
	{
		temp =(float) ((temp - 0x06F2) *  40)  / 0x00D5 + 340.0f;
	}
	else if (code > 0x07C7 && code <= 0x089F)	//380~420
	{
		temp =(float) ((temp - 0x07C7) * 40)  / 0x00D8 + 380.0f;
	}

	else if (code > 0x089F && code <= 0x0978)	//420~460
	{
		temp = (float)((temp - 0x089F) * 40) / 0x00D9 + 420.0f;
	}
	else if (code > 0x0978 && code <=0x0A52)	//460~500
	{
		temp =(float)((temp - 0x0978) * 40) / 0x00DA + 460.0f;
	}
	else
	{
		temp = 0xA5A5;
	}
	
	t = (int)(10*temp);

	return t;
}



/**************************************************************
 * function: readCelcius()
 * introduction: returns the celcius temperature value as a double
 * return value: converted temperature value
 **************************************************************/

double thermocouple_readCelcius(unsigned int channel){

	signed int local_data, far_data, compensation;
	signed int temp;
	double tempConv;

	local_data = thermocouple_ADSread(1, channel);
	far_data = thermocouple_ADSread(0, channel);
	compensation = thermocouple_localCompensation(local_data);
	temp = far_data + compensation;
	temp = thermocouple_ADCcode2temp(temp & 0xFFFF) ;
	tempConv = (double)(temp);
	tempConv = tempConv/10;

	return tempConv;
}

float tcTempRead(unsigned char tc_sel){

	int j = 0;	
	double temp[11]; 
	double sum = 0; 
	
	if(tc_sel == 1){
		if(firsttime1 == 0){
		//10 measures
		for(j = 0; j < 10; j++){
			//Populate buffer
			tc1measures[j] = thermocouple_readCelcius((unsigned int) tc_sel); 
		}	
		firsttime1 = 1;	
		
		}else{
		//Shift buffer - old sample discarted 
		for(j = 0; j< 10; j++){
			temp[j] = 0.0;
			temp[j]= tc1measures[j]; 
		}	

		temp[10] = 0.0;

		for(j = 0; j< 10; j++){
			tc1measures[j] = temp[j+1];
		}

		tc1measures[9] = thermocouple_readCelcius((unsigned int) tc_sel);  
		}

		sum = 0; 
		for(j = 0; j< 10; j++){
			sum = sum + tc1measures[j];
		}

		return (float)(sum/10.0);

	}else{

		if(firsttime2 == 0){
		//10 measures	
		for(j = 0; j < 10; j++){
			//Populate buffer
			tc2measures[j] = thermocouple_readCelcius((unsigned int) tc_sel); 
		}	
		firsttime2 = 1;	
		
		}else{
		//Shift buffer - old sample discarted 

		for(j = 0; j< 10; j++){
			temp[j] = 0.0;
			temp[j]= tc2measures[j]; 
		}	

		temp[10] = 0.0;

		for(j = 0; j< 10; j++){
			tc2measures[j] = temp[j+1]; 
		}

		tc2measures[9] = thermocouple_readCelcius((unsigned int) tc_sel);  
		}
		
		sum = 0;  
		for(j=0; j< 10; j++){
			sum = sum + tc2measures[j];
		}

		return (float)(sum/10.0);

	}

}

void tcConfig(){

	thermocouple_ADSread(0,1); 
	Delayms(3000); 

}
