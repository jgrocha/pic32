#include <plib.h>
#include "adc.h"
#include "HardwareProfile.h"

unsigned int anaCh[5];		// conversion result as read from result buffer

unsigned int channel4;	// conversion result as read from result buffer
unsigned int channel5;	// conversion result as read from result buffer
unsigned int offset;	// buffer offset to point to the base of the idle buffer

unsigned int DmaBuffer = 0;

/************************************************************
Function name:	adc1Config
Description:	configure ADC1
Parameter:		none
Return Value:	none
************************************************************/
void adcConfig(void)
{
	// configure and enable the ADC
	CloseADC10();	// ensure the ADC is off before setting the configuration
	
	// define setup parameters for OpenADC10
	// 				Turn module on | ouput in integer | trigger mode auto | enable autosample
	#define PARAM1  ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
	
	// define setup parameters for OpenADC10
	// 				ADC ref external    | disable offset test    | disable scan mode | perform 2 samples | use dual buffers | use alternate mode
	#define PARAM2  ADC_VREF_EXT_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_15 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
	
	// define setup parameters for OpenADC10
	//				  use ADC internal clock | set sample time
	#define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
	
	
	// define setup parameters for OpenADC10
	//               set AN4 and AN5 as analog inputs
	#define PARAM4	ENABLE_AN10_ANA | ENABLE_AN11_ANA | ENABLE_AN12_ANA | ENABLE_AN13_ANA | ENABLE_AN14_ANA 
	
	
	// define setup parameters for OpenADC10
	// do not assign channels to scan
	#define PARAM5	SKIP_SCAN_AN0 | SKIP_SCAN_AN1 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN4 | \
					SKIP_SCAN_AN5 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | \
					SKIP_SCAN_AN15 
	
	// use ground as neg ref for A | use AN4 for input A      |  use ground as neg ref for A | use AN5 for input B
	
	// configure to sample AN4 & AN5
	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN10 | ADC_CH0_POS_SAMPLEA_AN11 \
					| ADC_CH0_POS_SAMPLEA_AN12 | ADC_CH0_POS_SAMPLEA_AN13 | ADC_CH0_POS_SAMPLEA_AN14); // configure to sample AN4 & AN5
					
	OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using the parameters defined above
	
	EnableADC10(); // Enable the ADC
}

/************************************************************
Function name:	adcRead
Description:	Reads adc channels
Parameter:		none
Return Value:	none
				Read Output is made to global variable anaCh
************************************************************/
void adcRead(void)
{
	unsigned int adcVal = 0;
	
	while ( ! mAD1GetIntFlag() ) 
    { 
        // wait for the first conversion to complete so there will be valid data in ADC result registers
    }

	// the results of the conversions are available
	
	anaCh[ANA_IN2] = ReadADC10(10);  		// read the result of channel ANA_IN2_CH
	anaCh[ANA_IN3] = ReadADC10(11);  		// read the result of channel ANA_IN3_CH
	anaCh[ANA_IN0] = ReadADC10(12);  		// read the result of channel ANA_IN0_CH
	anaCh[ANA_IN1] = ReadADC10(13);  		// read the result of channel ANA_IN1_CH
	anaCh[BOARD_TEMP] = ReadADC10(14); 		// read the result of channel BOARD_TEMP_CH
		
	mAD1ClearIntFlag();

/*#ifdef DEBUG_ADC
	printf("\nADC:\t\t%d\t%d\t%d\t%d\t%d\n", anaCh[0], anaCh[1], anaCh[2], anaCh[3], anaCh[4]);
#endif*/

}
