#include <plib.h>
#include <string.h>
#include "HardwareProfile.h"
#include "uart.h"


extern struct Node* head;

unsigned char UART2RxBuf[64];

unsigned char TESTE_DO_BRITO;

unsigned char UART2RxBufLen = 0;

/************/
/* Module 2 */
/************/
/************************************************************
Function name:	uart2Config
Description:	This function configures the UART2 module and 
					sets the baud rate value
Parameter:		interrupt - enable/disable interrupt
				prior	  - set priority
Return Value:	none
************************************************************/
void UART2Config(void)
{
	UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY);
	UARTSetFifoMode(UART2, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
	UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
	UARTSetDataRate(UART2, GetPeripheralClock(), DESIRED_BAUDRATE);
	UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
	
	// Configure UART2 RX Interrupt
	INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
	INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_2);
	INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_0);
}

void UART2WriteString(const char *string)
{
	while (*string != '\0')
	{
		while (!UARTTransmitterIsReady(UART2));
		
		UARTSendDataByte(UART2, *string);
		
		string++;
		
		while (!UARTTransmissionHasCompleted(UART2));
	}
}

void UART2PutCharacter(const char character)
{
	while (!UARTTransmitterIsReady(UART2));
	
	UARTSendDataByte(UART2, character);
	
	while (!UARTTransmissionHasCompleted(UART2));
}

// UART 2 interrupt handler
// it is set at priority level 2 with software context saving
void __ISR(_UART2_VECTOR, IPL2SOFT) IntUart2Handler(void)
{
	unsigned char i=0;
    struct Node* novo = NULL;
	
	// Is this an RX interrupt?
	if (INTGetFlag(INT_SOURCE_UART_RX(UART2)))
	{
		UART2RxBuf[UART2RxBufLen] = UARTGetDataByte(UART2);
//		UART2RxBuf[UART2RxBufLen+1]= '\0';
		
        TESTE_DO_BRITO = UART2RxBuf[UART2RxBufLen];

        if(UART2RxBuf[UART2RxBufLen] == '\r' || UART2RxBuf[UART2RxBufLen] == '\n') {
            if (UART2RxBufLen > 0) {
                novo  = (struct Node*)malloc(sizeof(struct Node));
                novo-> mensagem = malloc(UART2RxBufLen + 1); 
                /// ok // memset(novo-> mensagem, '\0', sizeof(novo-> mensagem));
                strncpy(novo-> mensagem, UART2RxBuf, UART2RxBufLen);
                // o space desaparece
                (novo-> mensagem)[UART2RxBufLen] = '\0';
                novo->next = head;
                head = novo;
            }
            UART2RxBufLen = 0;
        } else {
            if(UART2RxBufLen < UART2_LEN)
                UART2RxBufLen++;
            else 
                UART2RxBufLen = 0;
        }
        
		// Clear the RX interrupt Flag
		INTClearFlag(INT_SOURCE_UART_RX(UART2));	
        
	}
	
	// We don't care about TX interrupt
	if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) )
	{
		INTClearFlag(INT_SOURCE_UART_TX(UART2));
	}
}

