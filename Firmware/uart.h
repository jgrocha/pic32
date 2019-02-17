#ifndef _UART_H_
#define	_UART_H_

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
void UART2Config(void);

void UART2WriteString(const char *string);

void UART2PutCharacter(const char character);


#endif

struct Node  
{ 
  // char mensagem[64];  
  char * mensagem;
  struct Node *next; 
}; 