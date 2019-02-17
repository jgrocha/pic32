#ifndef _THERMOCOUPLE_H_
#define _THERMOCOUPLE_H_

//ADS1118 Module Defs

#define TC_ENABLE	0
#define TC_DISABLE 	1

#define ADS1118_OS             (0x8000)         //
#define ADS1118_CH0            (0x0000)         //
#define ADS1118_CH1            (0x3000)         //
#define ADS1118_GAIN0          (0x0000)         //
#define ADS1118_GAIN1          (0x0200)         //
#define ADS1118_GAIN2          (0x0400)         //
#define ADS1118_GAIN4          (0x0600)         //
#define ADS1118_GAIN8          (0x0800)         //
#define ADS1118_GAIN16         (0x0A00)         //
#define ADS1118_PWRDOWN        (0x0100)         //

#define ADS1118_RATE8SPS       (0x0000)         //
#define ADS1118_RATE16SPS      (0x0020)         //
#define ADS1118_RATE32SPS      (0x0040)         //
#define ADS1118_RATE64SPS      (0x0060)         //
#define ADS1118_RATE128SPS     (0x0080)         //
#define ADS1118_RATE250SPS     (0x00A0)         //
#define ADS1118_RATE475SPS     (0x00C0)         //
#define ADS1118_RATE860SPS     (0x00E0)         //

#define ADS1118_TS			   (0x0010)         //
#define ADS1118_PULLUP     	   (0x0008)         //
#define ADS1118_NOP     	   (0x0002)         //
#define ADS1118_CNVRDY     	   (0x0001)         //

//Set the configuration to AIN0/AIN1, FS=+/-0.256, SS, DR=128sps, PULLUP on DOUT
#define ADSCON_CH0		(0x8B8A)

//Set the configuration to AIN2/AIN3, FS=+/-0.256, SS, DR=128sps, PULLUP on DOUT
#define ADSCON_CH1		(0xBB8A)

//Set the configuration to AIN0/AIN1, FS=+/-2.048, SS, DR=128sps, PULLUP on DOUT
//#define ADSCON_CH0		(0x858A)

//Set the configuration to AIN2/AIN3, FS=+/-2.048, SS, DR=128sps, PULLUP on DOUT
//#define ADSCON_CH1		(0xB58A)

/* Function Defines */
int thermocouple_writeSpi (unsigned int config, int mode);
int thermocouple_ADSread(unsigned int mode, unsigned int channel);
int thermocouple_localCompensation(int local_code);
int thermocouple_ADCcode2temp(int code);
double thermocouple_readCelcius(unsigned int channel); 
float tcTempRead(unsigned char tc_sel);
void tcConfig(); 

#endif
