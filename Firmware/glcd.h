#ifndef _GLCD_H_
#define _GLCD_H_

#define ON						1
#define OFF						0



#define DISPLAY_ON_CMD			0b00111110
#define DISPLAY_SET_Y			0b01000000
#define DISPLAY_SET_X			0b10111000
#define DISPLAY_START_LINE		0b11000000

#define DISPLAY_STATUS_BUSY		0b10000000

#define CHIP1			0
#define CHIP2			1
#define CHIP3			2
#define CHIP_ALL		3

#define SCREEN_WIDTH	192

typedef union
{
	unsigned char db;
	
	struct
	{
		unsigned char db0		:4;
		unsigned char reset		:1;
		unsigned char on		:1;
		unsigned char db1		:1;
		unsigned char busy		:1;
	};	
} LCD_STATUS;

LCD_STATUS lcdStatus[3];

void GLCD_BacklightOn(unsigned char state);

void GLCD_DataInput(void);

unsigned char GLCD_GetData(void);

void GLCD_DataOutput(void);

void GLCD_SendData(unsigned char data);

void GLCD_Initialize(void);

void GLCD_Delay(void);

void GLCD_EnableController(unsigned char controller);

void GLCD_DisableController(unsigned char controller);

unsigned char GLCD_ReadStatus(unsigned char controller);

void GLCD_BusyWait(unsigned char controller);

void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller);

unsigned char GLCD_ReadData(void);

void GLCD_WriteData(unsigned char dataToWrite);
 
unsigned char GLCD_ReadByteFromROMMemory(char *ptr);

void GLCD_GoTo(unsigned char x, unsigned char y);

void GLCD_WriteChar(char charToWrite, unsigned char mode);

void GLCD_WriteString(char *stringToWrite, unsigned char mode);

void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color);
 
void GLCD_Bitmap(char *bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy,unsigned char mode);
 
void GLCD_Line(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char color);
 
void GLCD_Rectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color);
 
void GLCD_Circle(unsigned char cx, unsigned char cy, unsigned char radius, unsigned char color);

void GLCD_WriteBigChar(char charToWrite,unsigned char mode);

void GLCD_WriteBigString(char *stringToWrite, unsigned char mode);

#endif
