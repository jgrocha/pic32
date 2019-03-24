/********************************************************************
 FileName:      HardwareProfile - PIC32MX795F512L PIM.h
 Dependencies:  See INCLUDES section
 Processor:     PIC32 USB Microcontrollers
 Hardware:      PIC32MX460F512L PIM
 Compiler:      Microchip C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the Company) for its PIC Microcontroller is intended and
 supplied to you, the Companys customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN AS IS CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC32MX795F512L_H
#define HARDWARE_PROFILE_PIC32MX795F512L_H

//---------------------------------//
//------------DEBUG FLAGS----------//
//---------------------------------//
#define DEBUG_TC			//DEBUG da leitura dos termopares
//#define DEBUG_FRAM
//#define DEBUG_LCD
#define DEBUG_ADC
#define DEBUG_RTC			//DEBUG da RTC
#define DEBUG_OUTPUTS		//DEBUG das saidas digitais (leds)
//#define DEBUG_INPUTS		//DEBUG das entradas digitais
//#define DEBUG_KEYBOARD  	//DEBUG do teclado de 9 botoes
//#define DEBUG_SD1			//DEBUG com as funcoes que criam um sistema de ficheiros no cartao
//#define DEBUG_SD2			//DEBUG com as funcoes que escrevem diretamente na memoria
//#define DEBUG_SD3 		//DEBUG depois de se efectuarem alteracoes nos ficheiros .txt atraves do PC
//#define DEBUG_CAN			//DEBUG das funcoes do CAN	



    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISDbits.TRISD15    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISFbits.TRISF8    // Input
    #define USB_BUS_SENSE       1 

    /*******************************************************************/
    /******** MDD File System selection options ************************/
    /*******************************************************************/
    #define ERASE_BLOCK_SIZE        4096
    #define WRITE_BLOCK_SIZE        4096


    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    
    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define PIC32MX795F512L
    
    /** CPU Clock Speed Assignment *************************************/
    //#define RUN_AT_48MHZ
    //#define RUN_AT_24MHZ
    #define RUN_AT_60MHZ

    // Various clock values
    #if defined(RUN_AT_48MHZ)
        #define GetSystemClock()            48000000UL
        #define GetPeripheralClock()        48000000UL
        #define GetInstructionClock()       (GetSystemClock())
    #elif defined(RUN_AT_24MHZ)
        #define GetSystemClock()            24000000UL
        #define GetPeripheralClock()        24000000UL
        #define GetInstructionClock()       (GetSystemClock())
    #elif defined(RUN_AT_60MHZ)    
        #define GetSystemClock()            (60000000ul)
        #define GetPeripheralClock()        (GetSystemClock()) 
        #define GetInstructionClock()       (GetSystemClock())
    #else
        #error Choose a speed
    #endif
   
    /* CORE TIMER CONFIGURATION */
    #define TOGGLES_PER_SEC					1		
	#define CORE_TICK_RATE	       			(GetSystemClock()/2/TOGGLES_PER_SEC)

	/* UART2 CONFIGURATION */
	#define DESIRED_BAUDRATE              	(230400)  //The desired BaudRate
	/* #define DESIRED_BAUDRATE              	(115200)      //The desired BaudRate */
	/* #define DESIRED_BAUDRATE              	(57600)      //The desired BaudRate */
	/* #define DESIRED_BAUDRATE              	(9600)      //The desired BaudRate */
	#define UART2_LEN						128

	/* I2C CONFIGURATION */
	#define I2C_CLOCK_FREQ              	100000
	
	// EEPROM Constants
	#define RTC_I2C_BUS              		I2C1
	#define RTC_ADDR_W              		0b11010000	//Write RTC address
	#define RTC_ADDR_R						0b11010001	//Read RTC address
	
	/* ADC Constants */
	#define	ANA_IN0							0
	#define	ANA_IN1							1
	#define	ANA_IN2							2
	#define	ANA_IN3							3
	#define BOARD_TEMP						4
	
	#define ANA_IN2_CH						10
	#define ANA_IN3_CH						11
	#define ANA_IN0_CH						12
	#define ANA_IN1_CH						13
	#define BOARD_TEMP_CH					14

	/** I/O pin configurations *****************************************/
	
	/* PORTA */
	#define LCD_CS3		PORTAbits.RA0
	#define TMP1CS		PORTAbits.RA1
	#define HOLD		PORTAbits.RA2
	#define CS_FRAM		PORTAbits.RA3
	#define WP1			PORTAbits.RA4
	#define LCD_BL		PORTAbits.RA5
	#define OUT14		PORTAbits.RA6
	#define OUT15		PORTAbits.RA7
	#define ADC_VREF	PORTAbits.RA10
	
	/* PORTB */
	#define KB_X0		PORTBbits.RB2
	#define KB_X1		PORTBbits.RB3
	#define KB_X2		PORTBbits.RB4
	#define KB_X3		U1OTGCONbits.VBUSON
	#define KB_Y0		PORTBbits.RB6
	#define KB_Y1		PORTBbits.RB7
	#define KB_Y2		PORTBbits.RB8
	#define KB_Y3		PORTBbits.RB9
	#define AN2			PORTBbits.RB10
	#define AN3			PORTBbits.RB11
	#define AN0			PORTBbits.RB12
	#define AN1			PORTBbits.RB13
	#define TEMPOUT1	PORTBbits.RB14
	
	/* PORTC */
	#define S0			PORTCbits.RC1
	#define S1			PORTCbits.RC2
	#define S2			PORTCbits.RC3
	#define OUT4		PORTCbits.RC13
	#define OUT6 		PORTCbits.RC14
	
	/* PORTD */
	#define OC1			PORTDbits.RD1
	#define OC2			PORTDbits.RD2
	#define OUT7		PORTDbits.RD3
	#define BUZZER		PORTDbits.RD4
	#define OUT9		PORTDbits.RD5
	#define OUT10		PORTDbits.RD6
	#define OUT11		PORTDbits.RD7
	#define OUT1		PORTDbits.RD8
	#define OUT2		PORTDbits.RD9
	#define OUT3		PORTDbits.RD11
	#define OUT8		PORTDbits.RD12
	#define CS_CFC		PORTDbits.RD13
	#define E1			PORTDbits.RD14
	#define OE			PORTDbits.RD15
	
	/* PORTE */
	#define LCD_D0		PORTEbits.RE0
	#define LCD_D1		PORTEbits.RE1
	#define LCD_D2		PORTEbits.RE2
	#define LCD_D3		PORTEbits.RE3
	#define LCD_D4		PORTEbits.RE4
	#define LCD_D5		PORTEbits.RE5
	#define LCD_D6		PORTEbits.RE6
	#define LCD_D7		PORTEbits.RE7
	#define INT_RTC 	PORTEbits.RE8
	#define LCD_EN		PORTEbits.RE9

	/* PORTF */
	#define S3			PORTFbits.RF2
	//#define IN_EN		PORTFbits.RF3
	#define LD_SYS		PORTFbits.RF12
	#define TMP2CS		PORTFbits.RF13
	#define DIR1		PORTFbits.RF8
	#define DIR2		PORTFbits.RF3
	
	/* PORTG */
	#define OUT13		PORTGbits.RG0
	#define OUT12		PORTGbits.RG1
	#define LCD_RW		PORTGbits.RG6
	#define LCD_RS		PORTGbits.RG7
	#define LCD_CS1		PORTGbits.RG8
	#define LCD_CS2		PORTGbits.RG9
	#define KEYB		PORTGbits.RG12
	#define OUT16		PORTGbits.RG13
	#define OUT5		PORTGbits.RG14
	#define LCD_RES		PORTGbits.RG15

    /** LED ************************************************************/
 /*   #define mInitAllLEDs()      LATA &= 0xFFC3; TRISA &= 0xFFC3;
    
    #define mLED_1              LATAbits.LATA2
    #define mLED_2              LATAbits.LATA3
    #define mLED_3              LATAbits.LATA4
    #define mLED_4              LATAbits.LATA5
    
    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_3()         mLED_3
    #define mGetLED_4()         mLED_4

    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_3_On()         mLED_3 = 1;
    #define mLED_4_On()         mLED_4 = 1;
    
    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_3_Off()        mLED_3 = 0;
    #define mLED_4_Off()        mLED_4 = 0;
    
    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_3_Toggle()     mLED_3 = !mLED_3;
    #define mLED_4_Toggle()     mLED_4 = !mLED_4;
	*/
    
    /** SWITCH *********************************************************/
/*	#define mInitSwitch2()      TRISDbits.TRISD6=1;
    #define mInitSwitch3()      TRISDbits.TRISD7=1;
    #define mInitAllSwitches()  mInitSwitch2();mInitSwitch3();
    #define sw2                 PORTDbits.RD6
    #define sw3                 PORTDbits.RD7
*/
    /** POT ************************************************************/
 	// #define mInitPOT()  {AD1PCFGbits.PCFG5 = 0;    AD1CON2bits.VCFG = 0x0;    AD1CON3bits.ADCS = 0xFF;    AD1CON1bits.SSRC = 0x0;    AD1CON3bits.SAMC = 0x10;    AD1CON1bits.FORM = 0x0;    AD1CON2bits.SMPI = 0x0;    AD1CON1bits.ADON = 1;}

    /** MDD File System error checks ***********************************/
    // Will generate an error if the clock speed is too low to interface to the card
    #if (GetSystemClock() < 100000)
        #error Clock speed must exceed 100 kHz
    #endif    

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0
    
    /*******************************************************************/
    /******** MDD File System selection options ************************/
    /*******************************************************************/
    #define USE_PIC32
    #define USE_32BIT

    #define USB_USE_MSD
    #define USE_SD_INTERFACE_WITH_SPI
    #define MEDIA_SOFT_DETECT

	//SPI Configuration
	#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
    #define SPI_START_CFG_2     (SPI_ENABLE)

    // Define the SPI frequency
    #define SPI_FREQUENCY		(20000000)

    #define SD_CS				PORTDbits.RD13
    #define SD_CS_TRIS			TRISDbits.TRISD13
    
    #define SD_CD				1				
    #define SD_CD_TRIS			
    
    #define SD_WE				0				
    #define SD_WE_TRIS			

    // Registers for the SPI module you want to use
    #define SPICON1				SPI1CON
    #define SPISTAT				SPI1STAT
    #define SPIBUF				SPI1BUF
    #define SPISTAT_RBF			SPI1STATbits.SPIRBF
    #define SPICON1bits			SPI1CONbits
    #define SPISTATbits			SPI1STATbits
    #define SPIENABLE           SPICON1bits.ON
    #define SPIBRG			    SPI1BRG
    // Tris pins for SCK/SDI/SDO lines
    #define SPICLOCK			TRISDbits.TRISD10
    #define SPIIN               TRISCbits.TRISC4
    #define SPIOUT				TRISDbits.TRISD0

    #define putcSPI             putcSPI1
    #define getcSPI             getcSPI1
    #define OpenSPI(config1, config2)   OpenSPI1(config1, config2)
         
    // Will generate an error if the clock speed is too low to interface to the card
    #if (GetSystemClock() < 100000)
        #error Clock speed must exceed 100 kHz
    #endif       
#endif  //HARDWARE_PROFILE_PIC32MX795F512L_H
