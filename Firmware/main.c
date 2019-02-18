/********************************************************************
 FileName:      main.c
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, dsPIC, and PIC32 USB Microcontrollers
 Hardware:      This demo is natively intended to be used on Microchip USB demo
                boards supported by the MCHPFSUSB stack.  See release notes for
                support matrix.  This demo can be modified for use on other 
                hardware platforms.
 Complier:      Microchip C18 (for PIC18), XC16 (for PIC24/dsPIC), XC32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

 ********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0   Initial release

  2.1   Updated for simplicity and to use common
        coding style

  2.7   Removed out-of-date description of PIC24F interrupt vector
        remapping requirements.

  2.8   Improvements to USBCBSendResume(), to make it easier to use.
  2.9   Added event transfer terminated handler code, so as to re-arm
        MSD bulk endpoint(s) following a clear endpoint halt.  This
        provides better error case checking/handling/recovery behavior
        in the case of malformed MSD host requests.
  2.9h  Adding new part support
  2.9j  Updates to support new bootloader features (ex: app version 
        fetching).
 ********************************************************************/

/** INCLUDES *******************************************************/
#include <math.h>
#include "USB/usb.h"
#include "./USB/usb_function_msd.h"

#include "HardwareProfile.h"
#include "MDD File System/FSIO.h"

#include "adc.h"
#include "buzzer.h"
#include "io.h"
#include "uart.h"
#include "rtc.h"
#include "matrixKeyboard.h"
#include "spi.h"
#include "fram.h"
#include "thermocouple.h"
#include "pwm.h"
#include "glcd.h"
#include "LCD_DATA.h"
//#include "LCD_FONTS.h"
#include "can.h"

/** CONFIGURATION **************************************************/
#pragma config UPLLEN   = ON        	// USB PLL Enabled
#pragma config FPLLMUL  = MUL_15        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx1      // ICE/ICD Comm Channel Select
#pragma config FUSBIDIO = OFF
#pragma config FVBUSONIO = OFF

/** VARIABLES ******************************************************/

// Let compile time pre-processor calculate the PR1 for timer 1(period)
#define SYS_FREQ             (60000000L)
#define PB_DIV                 1
#define PRESCALE               256
#define KEYBOARD_PER_SEC       5
#define T1_TICK               (SYS_FREQ/PB_DIV/PRESCALE/KEYBOARD_PER_SEC)


unsigned char ReceivedDataBuffer[64];
unsigned char ToSendDataBuffer[64];

USB_HANDLE USBOutHandle = 0; //Needs to be initialized to 0 at startup.
USB_HANDLE USBInHandle = 0; //Needs to be initialized to 0 at startup.
BOOL blinkStatusValid = TRUE;

//extern unsigned char UART2RxBuf;

struct Node *head = NULL;

extern unsigned char UART2RxBuf[64];

extern unsigned char UART2RxBufLen;
unsigned char str[20];

unsigned char flag1S = 0, flag1Min = 0, flagKeys = 0, updatetemp = 0;
unsigned char countSeconds;
unsigned char countSeconds2;
int countsec = 0;

extern unsigned int anaCh[5];
extern RTC rtc;
const char compilingDate[] = __DATE__;
const char compilingTime[] = __TIME__;

unsigned char tx[5] = {'1', '2', '3', '4', '5'};
unsigned char rx[5];
unsigned char tx2[5] = {'0', '0', '0', '0', '0'};
float tensao1 = 0.0;
float tensao2 = 0.0;

//int nr_vezes=0;
char buffer_sd[512];
char buffer_lido[512];
char buffer[] = "12345";
char sendString[] = "This is test string: ";
char receiveBuffer[50];

#if defined(__C30__) || defined(__C32__) || defined __XC16__
//The LUN variable definition is critical to the MSD function driver.  This
//  array is a structure of function pointers that are the functions that 
//  will take care of each of the physical media.  For each additional LUN
//  that is added to the system, an entry into this array needs to be added
//  so that the stack can know where to find the physical layer functions.
//  In this example the media initialization function is named 
//  "MediaInitialize", the read capacity function is named "ReadCapacity",
//  etc.  
LUN_FUNCTIONS LUN[MAX_LUN + 1] = {
    {
        &MDD_SDSPI_MediaInitialize,
        &MDD_SDSPI_ReadCapacity,
        &MDD_SDSPI_ReadSectorSize,
        &MDD_SDSPI_MediaDetect,
        &MDD_SDSPI_SectorRead,
        &MDD_SDSPI_WriteProtectState,
        &MDD_SDSPI_SectorWrite
    }
};
#endif

/* Standard Response to INQUIRY command stored in ROM 	*/
const ROM InquiryResponse inq_resp = {
    0x00, // peripheral device is connected, direct access block device
    0x80, // removable
    0x04, // version = 00=> does not conform to any standard, 4=> SPC-2
    0x02, // response is in format specified by SPC-2
    0x20, // n-4 = 36-4=32= 0x20
    0x00, // sccs etc.
    0x00, // bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
    // but as in case of other device, we are just using 00
    0x00, // 00 obsolete, 0x80 for basic task queueing
    {'M', 'i', 'c', 'r', 'o', 'c', 'h', 'p'},
    // this is the T10 assigned Vendor ID
    {'M', 'a', 's', 's', ' ', 'S', 't', 'o', 'r', 'a', 'g', 'e', ' ', ' ', ' ', ' '},
    {'0', '0', '0', '1'}
};

int li, lj;
int aux = 0;
unsigned int i;
unsigned int count = 0;
FSFILE * pointer;

//CAN Fifo
BYTE CAN1MessageFifoArea[2 * 8 * 16];

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
void USBDeviceTasks(void);
void ProcessIO(void);
void YourHighPriorityISRCode(void);
void YourLowPriorityISRCode(void);
void USBCBSendResume(void);
void UserInit(void);
void updatetemperature(void);

extern unsigned char TESTE_DO_BRITO;

/** DECLARATIONS ***************************************************/

const char *DELIMITERS = {" /,"};

/*
led/1 on
led/2 on
led/3 on
led/4 on
led/5 on
led/6 on
led/7 on
led/8 on
led/9 on
led/10 on
led/11 on
led/12 on
led/13 on
led/14 on
led/15 on
led/16 on
 * 
 * 
 * 
led/1 off
led/2 off
led/3 off
led/4 off
led/5 off
led/6 off
led/7 off
led/8 off
led/9 off
led/10 off
led/11 off
led/12 off
 * 
 * 
led/10 on
led/5 onled/12 on
led/10 on
led/5 on
 * 
 * 
led/12 off
led/10 off
led/5 off
led/20 on

 */
// adc/1 10.1
// buzzer/p 1
// buzzer/p 3

// dout/3 on
// din/3 on ???

// por fazer
// time  ???

void executaMensagem(char *mensagem) {
    char *partes[10];
    int numdepartes = 0, k;

    int led, ciclos, din, dacout;
    float tensao;
    unsigned char dinstatus = 0;

    char* copia = strdup(mensagem);
    char *token = strtok(copia, " /,");

    while (token != NULL) {
        // printf("Parte: %s\n", token);
        partes[numdepartes] = token;
        numdepartes++;
        token = strtok(NULL, " /,");
    }

    //    for (k = 0; k < numdepartes; k++) {
    //        printf("Parte: %s\n", partes[k]);
    //    }

    // leds = digital output
    // leds a funcionar: 3,4,6,7,9,10,14,15,16
    if (numdepartes == 3 && strcmp(partes[0], "led") == 0) {
        led = atoi(partes[1]);
        if (led >= 1 && led <= 17) {
            if (strcmp(partes[2], "on") == 0) {
                ioOutputCtrl(led, 1);
            } else {
                ioOutputCtrl(led, 0);
            }
            printf("%s done\n", mensagem);
        }
    }

    if (numdepartes == 2 && strcmp(partes[0], "din") == 0) {
        din = atoi(partes[1]);
        if (din >= 1 && din <= 16) {
            dinstatus = ioInputStatus(din);
            // printf("Entrada %d status %d\n", din, dinstatus);
            printf("din/%d %d\n", din, dinstatus);
            // printf("%s done\n", mensagem);
        }
    }

    // digital-to-analog (DAC)
    // dacout/1 5.0
    if (numdepartes == 3 && strcmp(partes[0], "dacout") == 0) {
        dacout = atoi(partes[1]);
        tensao = atof(partes[2]);
        if ((dacout >= 1 && dacout <= 2) && (tensao >= 0.0 && tensao <= 10.0)) {
            ioAnalogOutput(tensao, dacout);
            // printf("Tensao %f na saida DACOUT%d\n", tensao, dacout);
            printf("%s done\n", mensagem);
        }
    }

    if (numdepartes == 3 && strcmp(partes[0], "buzzer") == 0) {
        if (strcmp(partes[1], "p") == 0) {
            ciclos = atoi(partes[2]);
            while (ciclos) {
                buzzerCtrl(ON);
                Delayms(50);
                buzzerCtrl(OFF);
                ciclos--;
                if (ciclos)
                    Delayms(100);
            }
            printf("%s done\n", mensagem);
        }
    }

    free(copia);
}

struct Node* processaMensagens(struct Node *cabeca) {
    int k = 0;
    struct Node *penultimo;
    if (cabeca == NULL) {
        return NULL;
    } else {
        if (cabeca->next == NULL) {
            printf("%s todo\n", cabeca->mensagem);
            executaMensagem(cabeca->mensagem);
            free(cabeca->mensagem);
            free(cabeca);
            return NULL;
        } else {
            penultimo = cabeca;
            while (penultimo->next->next != NULL)
                penultimo = penultimo->next;
            printf("%s todo\n", penultimo->next->mensagem);
            executaMensagem(penultimo->next->mensagem);
            free(penultimo->next->mensagem);
            free(penultimo->next);
            penultimo->next = NULL;
            return cabeca;
        }
    }
}

void imprimeListaMensagens(struct Node *n) {
    int k = 0;
    printf("---8<-------------------------------------------------------\n");
    while (n != NULL) {
        printf("Mensagem %d: %s\n", k, n->mensagem);
        n = n->next;
        k++;
    }
    printf("---8<-------------------------------------------------------\n");
}

/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
int main(void) {
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    TRISA = 0xFF00;
    Nop();
    Nop();
    LATA = 0;
    Nop();
    Nop();
    TRISB = 0xFFC3;
    Nop();
    Nop();
    LATB = 0;
    Nop();
    Nop();
    TRISC = 0x9FF1;
    Nop();
    Nop();
    LATC = 0;
    Nop();
    Nop();
    TRISD = 0x4001;
    Nop();
    Nop();
    LATD = 0;
    Nop();
    Nop();
    //TRISE = 0xFC00;Nop();Nop();LATE=0;Nop();Nop();
    TRISE = 0xFD00;
    Nop();
    Nop();
    LATE = 0;
    Nop();
    Nop();
    TRISF = 0xCEF3;
    Nop();
    Nop();
    LATF = 0;
    Nop();
    Nop();
    TRISG = 0x803C;
    Nop();
    Nop();
    LATG = 0;
    Nop();
    Nop();

    InitializeSystem();

#if defined(USB_INTERRUPT)
    USBDeviceAttach();
#endif

#ifdef DEBUG_FRAM

    /*FRAM testing***************************************************************************/
    printf("\n************************************************************************");
    printf("\nTeste FRAM: \n");
    framWriteData(5, tx2, 5);
    printf("\nFRAM TX: %d\t%d\t%d\t%d\t%d", tx2[0], tx2[1], tx2[2], tx2[3], tx2[4], tx2[5]);
    framReadData(5, rx, 5);
    printf("\nFRAM RX: %d\t%d\t%d\t%d\t%d", rx[0], rx[1], rx[2], rx[3], rx[4], rx[5]);
    framWriteData(5, tx, 5);
    printf("\nFRAM TX: %d\t%d\t%d\t%d\t%d", tx[0], tx[1], tx[2], tx[3], tx[4], tx[5]);
    framReadData(5, rx, 5);
    printf("\nFRAM RX: %d\t%d\t%d\t%d\t%d", rx[0], rx[1], rx[2], rx[3], rx[4], rx[5]);
    printf("\n************************************************************************");

#endif


#ifdef DEBUG_SD1
    /*Testing MicroSD N.1********************************************************************/
    //Utilizando as funcoes FSIO
    while (!FSInit());

    printf("\n************************************************************************");
    printf("\nTESTE DO SD CARD N.1: \n");

    // Criar um novo ficheiro .txt
    pointer = FSfopen("TEST.TXT", "w");
    if (pointer == NULL) {
        printf("\nNao e possivel abrir o ficheiro!\n");
    }

    // Escrever no ficheiro Test.txt
    if (FSfwrite(sendString, 1, 22, pointer) != 22) {
        printf("\nNao foi possivel escrever no ficheiro!\n");
    } else {
        printf("\nEscrita efectuada com sucesso!\n");
    }

    // FSfseek sets the position one byte before the end
    // It can also set the position of a file forward from the
    // beginning or forward from the current position
    if (FSfseek(pointer, 1, SEEK_END) != 0) {
        printf("\nErro na funcao Fsfseek!\n");
    }

    // Write at the end of the string
    if (FSfwrite(tx, 1, 5, pointer) != 5) {
        printf("\nNao foi possivel escrever no ficheiro!\n");
    } else {
        printf("\nEscrita efectuada com sucesso!\n");
    }

    // Fechar o ficheiro
    if (FSfclose(pointer) == 0) {
        printf("\nFicheiro fechado com sucesso!\n");
    }

    // Abrir o ficheiro em modo de leitura
    pointer = FSfopen("TEST.TXT", "r");
    if (pointer == NULL) {
        printf("\nNao foi possivel abrir o ficheiro!\n");
    }

    // Ler 4 bytes do ficheiro
    if (FSfread(receiveBuffer, 4, 1, pointer) != 1) {
        printf("\nErro na leitura!\n");
    }

    // Fechar o ficheiro
    if (FSfclose(pointer) != 0) {
        printf("\nErro a fechar o ficheiro!\n");
    }

    // Testar se as leituras efectuadas estao correctas
    if ((receiveBuffer[0] != 'T') ||
            (receiveBuffer[1] != 'h') ||
            (receiveBuffer[2] != 'i') ||
            (receiveBuffer[3] != 's')) {
        printf("\nLeitura incorrecta!\n");
    } else {
        printf("\nLeitura correcta!\n");
    }

    // Criar arvore de diretorios
    if ((FSmkdir("ONE")) == 0) {
        printf("\nDiretorio criado!\n");
    }

    // Mudar para o diretorio ONE 
    if (FSchdir("ONE") != 0) {
        printf("\nErro!\n");
    }

    // Criar novo diretorio dentro da pasta ONE
    if ((FSmkdir("TWO")) == 0) {
        printf("\nDiretorio criado!\n");
    }

    // Criar novo ficheiro no diretorio ONE
    pointer = FSfopen("NEWFILE.TXT", "w");

    // Fechar o ficheiro 
    if (FSfclose(pointer) != 0) {
        printf("\nErro a fechar o ficheiro!\n");
    }

    MDD_SDSPI_ShutdownMedia();

    printf("************************************************************************\n\r");
#endif

#ifdef DEBUG_SD2
    /*Testing MicroSD N.2*******************************************************************/
    // Escrita e leitura diretamente na memoria do cartao SD - nao e possivel aceder pelo PC 

    while (!FSInit());

    printf("\n************************************************************************");
    printf("\nTESTE DO SD CARD N.2: \n");


    //Preencher o buffer de 512 para escrever no cartao
    for (li = 0; li < 256; li++) {
        buffer_sd[li] = 5;
    }

    for (li = 256; li < 512; li++) {
        buffer_sd[li] = 2;
    }

    // Escrever na posicao 0x00000001 do cartao a informacao contida no buffer_sd
    li = MDD_SDSPI_SectorWrite(0x00000001, buffer_sd, 0x00);

    // Verificar se a escrita foi efectuada com sucesso
    if (li > 0) {
        printf("Escrita no cartao efectuada com sucesso!\n");
    } else {
        printf("Escrita no cartao falhada!\n");

    }

    // Leitura do cartao
    MDD_SDSPI_SectorRead(0x00000001, buffer_lido);

    // Impressao do conteudo lido
    printf("Conteudo do buffer:");
    for (li = 0; li < 512; li++) {
        printf(" %d ", buffer_lido[li]);
    }

    MDD_SDSPI_ShutdownMedia();

    printf("\n************************************************************************\n\r");
#endif

#ifdef DEBUG_SD3
    /*Testing MicroSD N.3********************************************************************/
    // Depois de efectuar alteracoes nos ficheiros de texto atraves do computador

    while (!FSInit());

    printf("\n************************************************************************");
    printf("\nTESTE DO SD CARD N.3: \n");


    // Abrir o ficheiro em modo de leitura
    pointer = FSfopen("TEST.TXT", "r");
    if (pointer == NULL) {
        printf("\nNao foi possivel abrir o ficheiro!\n");
    }

    // Ler 4 bytes do ficheiro
    if (FSfread(receiveBuffer, 4, 1, pointer) != 1) {
        printf("\nErro na leitura!\n");
    }

    // Fechar o ficheiro
    if (FSfclose(pointer) != 0) {
        printf("\nErro a fechar o ficheiro!\n");
    }

    // Verificar se as leituras estao correctas
    if ((receiveBuffer[0] != '1') ||
            (receiveBuffer[1] != '5') ||
            (receiveBuffer[2] != '4') ||
            (receiveBuffer[3] != '2')) {
        printf("\nLeitura incorrecta!\n");
    } else {
        printf("\nLeitura correcta!\n");
    }

    MDD_SDSPI_ShutdownMedia();

    printf("************************************************************************\n\r");
#endif

    while (1) {

        //		#if defined(USB_POLLING)
        //        		USBDeviceTasks(); 
        //        #endif	

        // Application-specific tasks.
        // Application related code may be added here, or in the ProcessIO() function.
        ProcessIO();

    }//end while
}//end main

/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void) {
    AD1PCFG = 0xFFFF;
    AD1CSSL = 0x0000;

    // Configure the PIC32 core for the best performance
    // at the operating frequency. The operating frequency is already set to 
    // 60MHz through Device Config Registers
    SYSTEMConfigPerformance(60000000);

    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    //	The USB specifications require that USB peripheral devices must never source
    //	current onto the Vbus pin.  Additionally, USB peripherals should not source
    //	current on D+ or D- when the host/hub is not actively powering the Vbus line.
    //	When designing a self powered (as opposed to bus powered) USB peripheral
    //	device, the firmware should make sure not to turn on the USB module and D+
    //	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
    //	firmware needs some means to detect when Vbus is being powered by the host.
    //	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
    // 	can be used to detect when Vbus is high (host actively powering), or low
    //	(host is shut down or otherwise not supplying power).  The USB firmware
    // 	can then periodically poll this I/O pin to know when it is okay to turn on
    //	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
    //	peripheral device, it is not possible to source current on D+ or D- when the
    //	host is not actively providing power on Vbus. Therefore, implementing this
    //	bus sense feature is optional.  This firmware can be made to use this bus
    //	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
    //	HardwareProfile.h file.    
#if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
#endif

    //	If the host PC sends a GetStatus (device) request, the firmware must respond
    //	and let the host know if the USB peripheral device is currently bus powered
    //	or self powered.  See chapter 9 in the official USB specifications for details
    //	regarding this request.  If the peripheral device is capable of being both
    //	self and bus powered, it should not return a hard coded value for this request.
    //	Instead, firmware should check if it is currently self or bus powered, and
    //	respond accordingly.  If the hardware has been configured like demonstrated
    //	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
    //	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
    //	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
    //	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
    //	to it in HardwareProfile.h.
#if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN; // See HardwareProfile.h
#endif    

    UserInit();

    USBDeviceInit(); //usb_device.c.  Initializes USB module SFRs and firmware
    //variables to known states

}//end InitializeSystem

/******************************************************************************
 * Function:        void UserInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *
 * Note:            
 *
 *****************************************************************************/
void UserInit(void) {

    unsigned char Inputs = 0;
    /***********************************************************************************/
    /***Nao esquecer de comentar - 3 DE FEV 2015*****************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /*Initialize Core Timer - interrupts every 1/CORE_TICK_RATE*************************/
    //OpenCoreTimer(CORE_TICK_RATE);

    /*Set up the core timer interrupt with a prioirty of 2 and zero sub-priority********/
    //mConfigIntCoreTimer(CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0);	
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/


    /* Init ADS1118 module for thermocouple readings*/
    tcConfig();

    /*Testing buzzer********************************************************************/
    buzzerCtrl(ON);
    Delayms(50);
    buzzerCtrl(OFF);
    Delayms(100);
    buzzerCtrl(ON);
    Delayms(50);
    buzzerCtrl(OFF);

    /*Initialize UART2******************************************************************/
    UART2Config();

    /*Initialize ADC********************************************************************/
    adcConfig();

    /*Initialize SPI********************************************************************/
    spiConfig();

    /*Initialize LCD********************************************************************/
    GLCD_Initialize();

    /*Initialize CAN *******************************************************************/
    CAN1Init(0x201); //Initialize CAN with SID 0x201		    	    

    /*RTC Configuration, Update and Reading*********************************************/
    rtcConfig();
    rtcUpdate(00, 43, 0, 0, 17, 02, 19);
    // hour, minute, second, day of week, day of month, month, year
    // Date: 16-10-14
    // Time: 15:33:00

    /***********************************************************************************/
    /****Configuracao do timer - 3 DE FEV 2015******************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /* Configure Timer 1 using internal clock, 1:256 prescale***************************/
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, T1_TICK);
    // set up the timer interrupt with a priority of 2
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/
    /***********************************************************************************/

    /*Enable multi-vector interrupts****************************************************/
    INTEnableSystemMultiVectoredInt();
    INTEnableInterrupts();

    /*Testing UART2*********************************************************************/
    //    printf("\nBraga\n");
    //    sprintf(str, compilingDate);
    printf("geomaster/compiling/date %s\n", compilingDate);
    printf("geomaster/compiling/time %s\n", compilingTime);
    //    sprintf(str, compilingTime);
    //    printf(str);
    //    printf("\nHardware: Jose Camelo / Elton Ferreira\nFirmware: Miguel Ribeiro / Miguel Brito / Ana Santos\n");

    /*Testing RTC***********************************************************************/
    rtcRead();
//    rtcPrintTimeDate();

    /*Initialize the variable holding the handle for the last transmission**************/
    USBOutHandle = 0;
    USBInHandle = 0;
    blinkStatusValid = TRUE;

    /*Testing Outputs*******************************************************************/
    ioOutputCtrl(ALL, OFF);
    Delayms(10);


#ifdef DEBUG_OUTPUTS

    /*Testing digital outputs (leds)****************************************************/
    Delayms(100);
    for (li = 1; li < 17; li++) {
        ioOutputCtrl(li, 1);
        Delayms(10);
    }
    for (li = 1; li < 17; li++) {
        ioOutputCtrl(li, 0);
        Delayms(10);
    }
#endif

#ifdef DEBUG_LCD

    //Testing LCD***********************************************************************
    INTDisableInterrupts();
    GLCD_BacklightOn(1);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    GLCD_BacklightOn(0);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    GLCD_BacklightOn(1);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    GLCD_Bitmap((char*) sroque, 0, 0, 192, 64, 1);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    GLCD_ClearScreen();
    GLCD_Bitmap((char*) sroque, 0, 0, 192, 64, 0);
    Delayms(250);
    Delayms(250);
    Delayms(250);
    GLCD_ClearScreen();
    GLCD_GoTo(0, 0);
    INTEnableInterrupts();

#endif

    //ioOutputCtrl(ALL, OFF);
    //Delayms(10);

    /*Teste de Inputs*********************************************************************/
    for (li = 1; li < 17; li++) {
        Inputs = ioInputStatus(li);

#ifdef DEBUG_INPUTS

        if (li == 1) {
            printf("\n************************************************************************");
            printf("\nTESTE Do Brito: \n");
        }

        switch (Inputs) {
            case 0: printf("A entrada %d nao esta activa!\n", li);
                break;
            case 1: printf("A entrada %d esta ativa!\n", li);
                break;
            case 2: printf("A entrada %d esta mal seleccionada!\n", li);
                break;
            default: break;
        }

        if (li == 16) {
            printf("************************************************************************\n\r");
        }

#endif
    }

    /*Teste das saidas analogicas 0-10V***************************************************/
    pwmInit();
    //    tensao1 = 10.0;
    //    tensao2 = 5.0;
    //    ioAnalogOutput(tensao1, 1);
    //    ioAnalogOutput(tensao2, 2);

}//end UserInit

/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void) {
    int i;
    static unsigned char lcdon = 0;
    float temp;
    unsigned char dinstatus = 0;
    static unsigned char dinstatus_anterior[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    static int anaCh_anterior[4] = {0, 0, 0, 0};

    if (updatetemp) {
        updatetemperature();
        updatetemp = 0;
        //        systemLedToggle();
    }

    // a cada segundo
    if (flag1S) {
        //Toggling System LED
        //        systemLedToggle();

        rtcRead();

        if (countSeconds++ == 60) {
            flag1Min = 1;
            countSeconds = 0;
        }

        /*Leitura das entradas analogicas (tensao, corrente e temperatura)******************************/
        adcRead();

#ifdef DEBUG_ADC
        //        printf("\nLEITURA DAS ENTRADAS ANALOGICAS: \n");
        //        printf("\nADC:\t\t%d\t%d\t%d\t%d\t%d\n", anaCh[0], anaCh[1], anaCh[2], anaCh[3], anaCh[4]);
        for (i = 0; i < 4; i++) {
            if (anaCh[i] != anaCh_anterior[i]) {
                anaCh_anterior[i] = anaCh[i];
                printf("adcout/%d %d\n", i, anaCh[i]);
            }
        }

#endif

        for (i = 1; i <= 16; i++) {
            dinstatus = ioInputStatus(i);
            if (dinstatus != dinstatus_anterior[i-1]) {
                dinstatus_anterior[i-1] = dinstatus;
                printf("din/%d %d\n", i, dinstatus);
            }
        }

        // imprimeListaMensagens(head);
        // head = processaMensagens(head);
        while (head != NULL)
            head = processaMensagens(head);

        flag1S = 0;
    }

    // a cada minuto
    if (flag1Min) {
//        printf("--Minuto--\n");
        printf("time/interval/sec 60\n");
        flag1Min = 0;
    }

    // User Application USB tasks
    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1)) return;

    MSDTasks();
}//end ProcessIO

void updatetemperature() {
    float temp;
    static float temp_anterior_1 = -999.9;
    static float temp_anterior_2 = -999.9;

#ifdef DEBUG_TC
    temp = tcTempRead(1);
    temp = floorf(temp * 10) / 10;
    if (temp < 40000.0f) {
        if (temp != temp_anterior_1) {
            temp_anterior_1 = temp;
            printf("tmp/1 %.1f\n", temp);
        }
    }
    temp = tcTempRead(2);
    temp = floorf(temp * 10) / 10;
    if (temp < 40000.0f) {
        if (temp != temp_anterior_2) {
            temp_anterior_2 = temp;
            printf("tmp/2 %.1f\n", temp);
        }
    }
#endif
}


/**************************************************************/
/*********************** INTERRUPTS ***************************/

/**************************************************************/
void __ISR(_CORE_TIMER_VECTOR, IPL2SOFT) CoreTimerHandler(void) {
    // clear the interrupt flag
    mCTClearIntFlag();

    // .. things to do
    //flag1S = 1; 

    // update the period - interrupts every 1/CORE_TICK_RATE - a cada 1s e gerada uma interrupcao
    //UpdateCoreTimer(CORE_TICK_RATE);
}

void __ISR(_EXTERNAL_1_VECTOR, IPL3SOFT) INT1Interrupt(void) {
    //nr_vezes++;
    //rtcRead();
    //Reset the alarm interrupt flag
    //rtcClearAlarmFlag(ALARM2FLAG);
    //rtcClearAlarmFlag(ALARM1FLAG);
    //Clear interrupt flag
    mINT1ClearIntFlag();
}

/***********************************************************************************/
/*** Timer 1 ISR - 3 DE FEV 2015 ***************************************************/
/***********************************************************************************/
/***********************************************************************************/
/***********************************************************************************/
// void __ISR(_TIMER_1_VECTOR, ipl2) Timer1Handler(void)

void __ISR(_TIMER_1_VECTOR, IPL2AUTO) Timer1Handler(void) {
    volatile unsigned char keyPressed = 0;
    countsec++;

    //	updatetemp = 1; 

    if (countsec == 5) {
        flag1S = 1;
        updatetemp = 1;
        countsec = 0;
    }

    // .. things to do
    //Verificar se alguma tecla esta a ser premida
    keyPressed = 0;
    keyPressed = keyboardRead();
    ClrWdt();

    if (keyPressed != 0) {
        GLCD_GoTo(16, 4);
        sprintf(str, "  ");
        GLCD_WriteString(str, 1);
        sprintf(str, "%d%", keyPressed);
        GLCD_GoTo(16, 4);
        GLCD_WriteString(str, 1);
        printf("\r\nTecla pressionada: %d% \n", keyPressed);
    }
    // clear the interrupt flag
    mT1ClearIntFlag();

}

/***********************************************************************************/
/***********************************************************************************/
/***********************************************************************************/
/***********************************************************************************/
/***********************************************************************************/


/* Timer 2 ISR */

/* Specify Interrupt Priority Level = 2, Vector 8 */
void __ISR(8, ipl2) _Timer2Handler(void) {
    // clear the interrupt flag
    mT2ClearIntFlag();

    // .. things to do ...
}

/* Timer 3 ISR */

/* Specify Interrupt Priority Level = 2, Vector 12 */
void __ISR(12, ipl2) _Timer3Handler(void) {
    // clear the interrupt flag
    mT3ClearIntFlag();

    // .. things to do ..
}

void __ISR(10, ipl5) _OC2Handler(void) {
    // clear the interrupt flag
    mOC2ClearIntFlag();

    // .. things to do ..
}

// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA* each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

// Note *: The "usb_20.pdf" specs indicate 500uA or 2.5mA, depending upon device classification. However,
// the USB-IF has officially issued an ECN (engineering change notice) changing this to 2.5mA for all 
// devices.  Make sure to re-download the latest specifications to get all of the newest ECNs.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void) {
    //Example power saving code.  Insert appropriate code here for the desired
    //application behavior.  If the microcontroller will be put to sleep, a
    //process similar to that shown below may be used:

    //ConfigureIOPinsForLowPower();
    //SaveStateOfAllInterruptEnableBits();
    //DisableAllInterruptEnableBits();
    //EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
    //Sleep();
    //RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
    //RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

    //IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
    //cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
    //things to not work as intended.	


#if defined(__C30__) || defined __XC16__
#if 0
    U1EIR = 0xFFFF;
    U1IR = 0xFFFF;
    U1OTGIR = 0xFFFF;
    IFS5bits.USB1IF = 0;
    IEC5bits.USB1IE = 1;
    U1OTGIEbits.ACTVIE = 1;
    U1OTGIRbits.ACTVIF = 1;
    Sleep();
#endif
#endif
}


/******************************************************************************
 * Function:        void _USB1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *					In this example the interrupt is only used when the device
 *					goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 *****************************************************************************/
#if 0

void __attribute__((interrupt)) _USB1Interrupt(void) {
#if !defined(self_powered)
    if (U1OTGIRbits.ACTVIF) {
        IEC5bits.USB1IE = 0;
        U1OTGIEbits.ACTVIE = 0;
        IFS5bits.USB1IF = 0;

        //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
        USBClearInterruptFlag(USBIdleIFReg, USBIdleIFBitNum);
        //USBSuspendControl = 0;
    }
#endif
}
#endif

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void) {
    // If clock switching or other power savings measures were taken when
    // executing the USBCBSuspend() function, now would be a good time to
    // switch back to normal full power run mode conditions.  The host allows
    // 10+ milliseconds of wakeup time, after which the device must be 
    // fully back to normal, and capable of receiving and processing USB
    // packets.  In order to do this, the USB module must receive proper
    // clocking (IE: 48MHz clock must be available to SIE for full speed USB
    // operation).  
    // Make sure the selected oscillator settings are consistent with USB 
    // operation before returning from this function.
}

/********************************************************************
 Function:        void USBCB_SOF_Handler(void)

 Description:     The USB host sends out a SOF packet to full-speed
                  devices every 1 ms. This interrupt may be useful
                  for isochronous pipes. End designers should
                  implement callback routine as necessary.

 PreCondition:    None
 
 Parameters:      None
 
 Return Values:   None
 
 Remarks:         None
 *******************************************************************/
void USBCB_SOF_Handler(void) {
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void) {
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

    // Typically, user firmware does not need to do anything special
    // if a USB error occurs.  For example, if the host sends an OUT
    // packet to your device, but the packet gets corrupted (ex:
    // because of a bad connection, or the user unplugs the
    // USB cable during the transmission) this will typically set
    // one or more USB error interrupt flags.  Nothing specific
    // needs to be done however, since the SIE will automatically
    // send a "NAK" packet to the host.  In response to this, the
    // host will normally retry to send the packet again, and no
    // data loss occurs.  The system will typically recover
    // automatically, without the need for application firmware
    // intervention.

    // Nevertheless, this callback function is provided, such as
    // for debugging purposes.
}

/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void) {
    USBCheckMSDRequest();
}//end

/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void) {
    // Must claim session ownership if supporting this request
}//end

/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void) {
#if (MSD_DATA_IN_EP == MSD_DATA_OUT_EP)
    USBEnableEndpoint(MSD_DATA_IN_EP, USB_IN_ENABLED | USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
#else
    USBEnableEndpoint(MSD_DATA_IN_EP, USB_IN_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
    USBEnableEndpoint(MSD_DATA_OUT_EP, USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
#endif

    USBMSDInit();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function will only be able to wake up the host if
 *                  all of the below are true:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *                  If the host has not armed the device to perform remote wakeup,
 *                  then this function will return without actually performing a
 *                  remote wakeup sequence.  This is the required behavior, 
 *                  as a USB device that has not been armed to perform remote 
 *                  wakeup must not drive remote wakeup signalling onto the bus;
 *                  doing so will cause USB compliance testing failure.
 *                  
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            This function does nothing and returns quickly, if the USB
 *                  bus and host are not in a suspended condition, or are 
 *                  otherwise not in a remote wakeup ready state.  Therefore, it
 *                  is safe to optionally call this function regularly, ex: 
 *                  anytime application stimulus occurs, as the function will
 *                  have no effect, until the bus really is in a state ready
 *                  to accept remote wakeup. 
 *
 *                  When this function executes, it may perform clock switching,
 *                  depending upon the application specific code in 
 *                  USBCBWakeFromSuspend().  This is needed, since the USB
 *                  bus will no longer be suspended by the time this function
 *                  returns.  Therefore, the USB module will need to be ready
 *                  to receive traffic from the host.
 *
 *                  The modifiable section in this routine may be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of ~3-15 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void) {
    static WORD delay_count;

    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if (USBGetRemoteWakeupStatus() == TRUE) {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if (USBIsBusSuspended() == TRUE) {
            USBMaskInterrupts();

            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0;
            USBBusIsSuspended = FALSE; //So we don't execute this code again, 
            //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;
            do {
                delay_count--;
            } while (delay_count);

            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1; // Start RESUME signaling
            delay_count = 1800U; // Set RESUME line for 1-13 ms
            do {
                delay_count--;
            } while (delay_count);
            USBResumeControl = 0; //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}

/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size) {
    switch ((INT) event) {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED:
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was 
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was 
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT 
            //      endpoints).

            //Check if the host recently did a clear endpoint halt on the MSD OUT endpoint.
            //In this case, we want to re-arm the MSD OUT endpoint, so we are prepared
            //to receive the next CBW that the host might want to send.
            //Note: If however the STALL was due to a CBW not valid condition, 
            //then we are required to have a persistent STALL, where it cannot 
            //be cleared (until MSD reset recovery takes place).  See MSD BOT 
            //specs v1.0, section 6.6.1.
            if (MSDWasLastCBWValid() == FALSE) {
                //Need to re-stall the endpoints, for persistent STALL behavior.
                USBStallEndpoint(MSD_DATA_IN_EP, IN_TO_HOST);
                USBStallEndpoint(MSD_DATA_OUT_EP, OUT_FROM_HOST);
            } else {
                //Check if the host cleared halt on the bulk out endpoint.  In this
                //case, we should re-arm the endpoint, so we can receive the next CBW.
                if ((USB_HANDLE) pdata == USBGetNextHandle(MSD_DATA_OUT_EP, OUT_FROM_HOST)) {
                    USBMSDOutHandle = USBRxOnePacket(MSD_DATA_OUT_EP, (BYTE*) & msd_cbw, MSD_OUT_EP_SIZE);
                }
            }
            break;
        default:
            break;
    }
    return TRUE;
}


/** EOF main.c ***************************************************************/

