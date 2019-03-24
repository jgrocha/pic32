#include <plib.h>
#include <string.h>
#include "HardwareProfile.h"
#include "uart.h"

unsigned int countinchar = 0;
unsigned int countin = 0; // lines = messages
unsigned int countindone = 0; // lines = messages 
unsigned char UART2RxBuf[UART2_LEN];
unsigned char UARTBuf[CAIXAS][UART2_LEN];
unsigned char novo_char;
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
void UART2Config(void) {
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

void UART2WriteString(const char *string) {
    while (*string != '\0') {
        while (!UARTTransmitterIsReady(UART2));

        UARTSendDataByte(UART2, *string);

        string++;

        while (!UARTTransmissionHasCompleted(UART2));
    }
}

void UART2PutCharacter(const char character) {
    while (!UARTTransmitterIsReady(UART2));

    UARTSendDataByte(UART2, character);

    while (!UARTTransmissionHasCompleted(UART2));
}

// UART 2 interrupt handler
// it is set at priority level 2 with software context saving
// IPL2SOFT
void __ISR(_UART2_VECTOR, IPL2SOFT) IntUart2Handler(void) {
    // Is this an RX interrupt?
    if (INTGetFlag(INT_SOURCE_UART_RX(UART2))) {
        while(!UARTReceivedDataIsAvailable(UART2));
        novo_char = UARTGetDataByte(UART2);
        countinchar++;
        if (novo_char == '\r' || novo_char == '\n'|| novo_char == '\0') {
            if (UART2RxBufLen > 0) {
                strncpy(UARTBuf[countin % CAIXAS], UART2RxBuf, UART2RxBufLen);
                UARTBuf[countin % CAIXAS][UART2RxBufLen] = '\0';
                systemLedToggle();
                countin++;
            }
            UART2RxBufLen = 0;
        } else {
            if (UART2RxBufLen < UART2_LEN) {
                UART2RxBuf[UART2RxBufLen] = novo_char;
                UART2RxBufLen++;
                // para debug
                UART2RxBuf[UART2RxBufLen] = '\0';
            } else
                UART2RxBufLen = 0;
        }
        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(UART2));
    }

    // We don't care about TX interrupt
    if (INTGetFlag(INT_SOURCE_UART_TX(UART2))) {
        INTClearFlag(INT_SOURCE_UART_TX(UART2));
    }
}