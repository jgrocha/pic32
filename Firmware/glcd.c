#include <plib.h>
#include <Compiler.h>
#include "glcd.h"
#include "HardwareProfile.h"
#include "LCD_FONTS.h"

const unsigned char ASCII_7x5[130][6] = {
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 0
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 1
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 2
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 3
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 4
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 5
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 6
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 7
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 8
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 9
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 10
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 11
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 12
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 13
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 14
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 15
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 16
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 17
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 18
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 19
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 20
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 21
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 22
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 23
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 24
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 25
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 26
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 27
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 28
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 29
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 30
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 31
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 32
{0x00,0x00,0x3D,0x00,0x00,0x00}, // ascii 33 -> !
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 34
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 35
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 36
{0x62,0x64,0x08,0x13,0x43,0x00}, // ascii 37 -> %
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 38
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 39
{0x00,0x1c,0x22,0x41,0x00,0x00}, // ascii 40 -> (
{0x00,0x41,0x22,0x1c,0x00,0x00}, // ascii 41 -> )
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 42
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 43
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 44
{0x08,0x08,0x08,0x08,0x08,0x00}, // ascii 45 -> -
{0x00,0x03,0x03,0x00,0x00,0x00}, // ascii 46
{0x02,0x04,0x08,0x10,0x20,0x00}, // ascii 47 -> /
{0x3e,0x47,0x49,0x51,0x3e,0x00}, // ascii 48 -> 0
{0x00,0x21,0x7f,0x01,0x00,0x00}, // ascii 49 -> 1
{0x21,0x43,0x45,0x49,0x31,0x00}, // ascii 50 -> 2
{0x41,0x41,0x51,0x69,0x46,0x00}, // ascii 51 -> 3
{0x0c,0x14,0x24,0x7f,0x04,0x00}, // ascii 52 -> 4
{0x72,0x51,0x51,0x51,0x4e,0x00}, // ascii 53 -> 5
{0x1e,0x29,0x49,0x49,0x06,0x00}, // ascii 54 -> 6
{0x40,0x47,0x48,0x50,0x60,0x00}, // ascii 55 -> 7
{0x36,0x49,0x49,0x49,0x36,0x00}, // ascii 56 -> 8
{0x30,0x49,0x49,0x4a,0x3c,0x00}, // ascii 57 -> 9
{0x00,0x66,0x66,0x00,0x00,0x00}, // ascii 58 -> :
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 59
{0x08,0x14,0x22,0x41,0x00,0x00}, // ascii 60 -> <
{0x14,0x14,0x14,0x14,0x14,0x00}, // ascii 61 -> =
{0x41,0x22,0x14,0x08,0x00,0x00}, // ascii 62 -> >
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 63
{0x00,0x00,0x00,0x00,0x00,0x00}, // ascii 64
{0x3f,0x44,0x44,0x44,0x3f,0x00}, // ascii 65 -> A
{0x7f,0x49,0x49,0x49,0x36,0x00}, // ascii 66 -> B
{0x3e,0x41,0x41,0x41,0x22,0x00}, // ascii 67 -> C
{0x7f,0x41,0x41,0x22,0x1c,0x00}, // ascii 68 -> D
{0x7f,0x49,0x49,0x49,0x41,0x00}, // ascii 69 -> E
{0x7f,0x48,0x48,0x48,0x40,0x00}, // ascii 70 -> F
{0x3e,0x41,0x49,0x49,0x2f,0x00}, // ascii 71 -> G
{0x7f,0x08,0x08,0x08,0x7f,0x00}, // ascii 72 -> H
{0x00,0x41,0x7f,0x41,0x00,0x00}, // ascii 73 -> I
{0x02,0x01,0x41,0x7e,0x40,0x00}, // ascii 74 -> J
{0x7f,0x08,0x14,0x22,0x41,0x00}, // ascii 75 -> K
{0x7f,0x01,0x01,0x01,0x01,0x00}, // ascii 76 -> L
{0x7f,0x20,0x18,0x20,0x7f,0x00}, // ascii 77 -> M
{0x7f,0x10,0x08,0x04,0x7f,0x00}, // ascii 78 -> N
{0x3e,0x41,0x41,0x41,0x3e,0x00}, // ascii 79 -> O
{0x7f,0x48,0x48,0x48,0x30,0x00}, // ascii 80 -> P
{0x3e,0x41,0x45,0x42,0x3d,0x00}, // ascii 81 -> Q
{0x7f,0x48,0x4c,0x4a,0x31,0x00}, // ascii 82 -> R
{0x31,0x49,0x49,0x49,0x46,0x00}, // ascii 83 -> S
{0x40,0x40,0x7f,0x40,0x40,0x00}, // ascii 84 -> T
{0x7e,0x01,0x01,0x01,0x7e,0x00}, // ascii 85 -> U
{0x7c,0x02,0x01,0x02,0x7c,0x00}, // ascii 86 -> V
{0x7e,0x01,0x0e,0x01,0x7e,0x00}, // ascii 87 -> W
{0x63,0x14,0x08,0x14,0x63,0x00}, // ascii 88 -> X
{0x70,0x08,0x07,0x08,0x70,0x00}, // ascii 89 -> Y
{0x43,0x45,0x49,0x51,0x61,0x00}, // ascii 90 -> Z
{0x00,0x7f,0x41,0x41,0x00,0x00}, // ascii 91 -> [
{0x20,0x10,0x08,0x04,0x02,0x00}, // ascii 92 -> Barra para Esquerda
{0x00,0x41,0x41,0x7f,0x00,0x00}, // ascii 93 -> ]
{0x00,0x00,0x00,0x00,0x00,0x00}, 
{0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00}, 
{0x06, 0x29, 0x29, 0x29, 0x1F}, //  a
{0xFF, 0x09, 0x11, 0x11, 0x0E}, //  b
{0x1E, 0x21, 0x21, 0x21, 0x12}, //  c
{0x0E, 0x11, 0x11, 0x09, 0xFF}, //  d
{0x0E, 0x15, 0x15, 0x15, 0x0C}, //  e
{0x08, 0x7F, 0x88, 0x80, 0x40}, //  f
{0x30, 0x49, 0x49, 0x49, 0x7E}, //  g
{0xFF, 0x08, 0x10, 0x10, 0x0F}, //  h
{0x00, 0x00, 0x5F, 0x00, 0x00}, //  i
{0x02, 0x01, 0x21, 0xBE, 0x00}, //  j
{0xFF, 0x04, 0x0A, 0x11, 0x00}, //  k
{0x00, 0x81, 0xFF, 0x01, 0x00}, //  l
{0x3F, 0x20, 0x18, 0x20, 0x1F}, //  m
{0x3F, 0x10, 0x20, 0x20, 0x1F}, //  n
{0x0E, 0x11, 0x11, 0x11, 0x0E}, //  o
{0x3F, 0x24, 0x24, 0x24, 0x18}, //  p
{0x10, 0x28, 0x28, 0x18, 0x3F}, //  q
{0x1F, 0x08, 0x10, 0x10, 0x08}, //  r
{0x09, 0x15, 0x15, 0x15, 0x02}, //  s
{0x20, 0xFE, 0x21, 0x01, 0x02}, //  t
{0x1E, 0x01, 0x01, 0x02, 0x1F}, //  u
{0x1C, 0x02, 0x01, 0x02, 0x1C}, //  v
{0x1E, 0x01, 0x0E, 0x01, 0x1E}, //  w
{0x11, 0x0A, 0x04, 0x0A, 0x11}, //  x
{0x00, 0x39, 0x05, 0x05, 0x3E}, //  y
{0x11, 0x13, 0x15, 0x19, 0x11}, //  z
};

unsigned char screen_x, screen_y;

void GLCD_BacklightOn(unsigned char state)
{
	LCD_BL = state; Nop();
}

void GLCD_DataInput(void)
{
	OE = 1; Nop();
	TRISFbits.TRISF3 = 0; Nop();
	DIR2 = 0; Nop();Nop();Nop();
	TRISE |= 0x00FF; 
	OE = 0; Nop();
}

unsigned char GLCD_GetData(void)
{
	return ((unsigned char)(PORTE & 0x00FF));
}

void GLCD_DataOutput(void)
{
	OE = 1; Nop();
	TRISFbits.TRISF3 = 0; Nop();
	DIR2 = 1; Nop();Nop();Nop();
	TRISE &= 0xFF00;
	OE = 0; Nop();
}

void GLCD_SendData(unsigned char data)
{
	PORTE |= ((unsigned int)data & 0x00FF);
}

void GLCD_Initialize(void)
{
	unsigned char i;
	TRISFbits.TRISF8 = 0;Nop();		// DIR1
	TRISFbits.TRISF3 = 0;Nop();		// DIR2
	TRISDbits.TRISD15 = 0; Nop();	// OE
	DIR1 = 1; Nop();
	DIR2 = 1; Nop();
	OE = 0; Nop();

	TRISGbits.TRISG6 = 0;Nop(); 	// RW 
	TRISGbits.TRISG7 = 0;Nop(); 	// RS 
	TRISGbits.TRISG8 = 0;Nop();		// CS1 
	TRISGbits.TRISG9 = 0;Nop();		// CS2  
	TRISGbits.TRISG15 = 0;Nop();	// RES
	TRISEbits.TRISE9 = 0;Nop(); 	// E  
	TRISAbits.TRISA0 = 0;Nop();		// CS3
	GLCD_Delay();	
	GLCD_DisableController(CHIP_ALL);
	GLCD_Delay();
	LCD_RES = 1;
	GLCD_Delay();GLCD_Delay();GLCD_Delay();GLCD_Delay();
	GLCD_WriteCommand((DISPLAY_ON_CMD | ON), 0);GLCD_DisableController(CHIP_ALL);
	GLCD_Delay();GLCD_Delay();GLCD_Delay();GLCD_Delay();
	GLCD_WriteCommand((DISPLAY_ON_CMD | ON), 1);GLCD_DisableController(CHIP_ALL);
	GLCD_Delay();GLCD_Delay();GLCD_Delay();GLCD_Delay();
	GLCD_WriteCommand((DISPLAY_ON_CMD | ON), 2);GLCD_DisableController(CHIP_ALL);
	GLCD_Delay();GLCD_Delay();GLCD_Delay();GLCD_Delay();
	GLCD_WriteCommand((DISPLAY_ON_CMD | ON), 3);GLCD_DisableController(CHIP_ALL);
	GLCD_Delay();GLCD_Delay();GLCD_Delay();GLCD_Delay();
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_ClearScreen(void)
{
    unsigned char   i, j;
 	//GLCD_Delay();
    for (j = 0; j < 8; j++) {
        GLCD_GoTo(0, j);
        for (i = 0; i < 192; i++) {
            GLCD_WriteData(255);
        }
    }
	//GLCD_Delay();
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_Delay(void)
{   
	unsigned char i;
	for(i=0;i<80;i++)
	{                                
		Nop();Nop();Nop();Nop();Nop();Nop();//Nop();Nop();Nop();Nop();
		//Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
	}
	ClrWdt();
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_EnableController(unsigned char controller)
{                                                        // Enable Controller (0-2)
	switch(controller) 
	{
		case CHIP1:
			LCD_CS1 = 0; Nop();
			break;           
		
		case CHIP2:
			LCD_CS2 = 0; Nop();
			break;                                                
		
		case CHIP3:
			LCD_CS3 = 0; Nop();
			break; 
			                                               
		case CHIP_ALL:
			LCD_CS1 = 0; Nop();Nop();Nop();Nop();
			LCD_CS2 = 0; Nop();Nop();Nop();Nop();
			LCD_CS3 = 0; Nop();Nop();Nop();Nop();
			break; 
			
		default:
			return;
	}
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_DisableController(unsigned char controller)
{                                                        // Disable Controller (0-2)
	switch(controller) 
	{
		case CHIP1:
			LCD_CS1 = 1; Nop();
			break;           
		
		case CHIP2:
			LCD_CS2 = 1; Nop();
			break;                                                
		
		case CHIP3:
			LCD_CS3 = 1; Nop();
			break; 
			                                               
		case CHIP_ALL:
			LCD_CS1 = 1; Nop();Nop();Nop();Nop();
			LCD_CS2 = 1; Nop();Nop();Nop();Nop();
			LCD_CS3 = 1; Nop();Nop();Nop();Nop();
			break; 
			
		default:
			return;
	}
}
 
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadStatus(unsigned char controller)
{
    unsigned char status;
 
    GLCD_DataInput();
    LCD_EN = 0; Nop();                                      	// EN moet laag hier zijn
    LCD_RW = 1; Nop();                                       	// RW hoog = lezen
    LCD_RS = 0; Nop();                                       	// RS laag = command
    GLCD_EnableController(controller);                        	// CSx laag
 
    GLCD_Delay();
    GLCD_Delay();
 
    LCD_EN = 1; Nop();                                       	// Nu pas EN hoog
 
   	GLCD_Delay();
   	GLCD_Delay();
   	
    LCD_EN = 0; Nop();                                			// EN laag
    GLCD_Delay();
    GLCD_Delay();
    status = GLCD_GetData();                         			// Status lezen
    
    GLCD_DisableController(controller);        					// CSx hoog
 	
 	GLCD_Delay();
 	GLCD_Delay();
   	
 	return status;     
}

void GLCD_BusyWait(unsigned char controller)
{
    unsigned char status, cnt;
   	
    while (1) 
	{
        lcdStatus[controller].db = GLCD_ReadStatus(controller);       	// Status lezen
        if (lcdStatus[controller].busy==0) {        					// Status-bit laag?
			return;                                        				// Terugkeren
        }
    }
}
 
//-------------------------------------------------------------------------------------------------
 
// Write command to specified controller
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller)
{                                                        		// Write command to specified controller 
    GLCD_BusyWait(controller);                                	// Wacht tot GLCD vrij is
    GLCD_DataOutput();
    LCD_EN = 0; Nop();                                        	// EN laag
    LCD_RW = 0; Nop();                                       	// RW laag
    LCD_RS = 0; Nop();                                       	// RS laag
    
    GLCD_Delay();
    GLCD_Delay();
    GLCD_Delay();
    
    GLCD_SendData(commandToWrite);                              // Data klaarzetten
    GLCD_EnableController(controller);                        	// CSx laag
 
    GLCD_Delay();
    GLCD_Delay();
 
    LCD_EN = 1; Nop();                                        	// EN hoog
 
    GLCD_Delay();
   	GLCD_Delay();
 
    LCD_EN = 0; Nop();                                       	// EN laag
    GLCD_Delay();
    GLCD_Delay();
    GLCD_DisableController(controller);                        	// CSx hoog
}
 
//-------------------------------------------------------------------------------------------------
 
// Read data from current position
unsigned char GLCD_ReadData(void)
{                                                        		// Read data from current position
    unsigned char Display_Data;
 
    GLCD_BusyWait(screen_x / 64);                        		// Wacht tot GLCD vrij is
    GLCD_DataInput();                                        	// PORTE = ingangen
    LCD_RW = 1; Nop();                                       	// RW hoog
    LCD_RS = 1; Nop();                                       	// RS hoog
    GLCD_EnableController(screen_x / 64);                		// CSx laag
 
    GLCD_Delay();
 
    LCD_EN = 1; Nop();                                        	// EN hoog
 
    GLCD_Delay();                                               // 1 NOP = 62nS bij 16 MIPS
 	GLCD_Delay();
 	
    Display_Data = GLCD_GetData();                     			// Data lezen
    LCD_EN = 0; Nop();                                        	// EN laag
    GLCD_DisableController(screen_x / 64);                		// CSx hoog
    screen_x++;
    
    return Display_Data;
}
 
//-------------------------------------------------------------------------------------------------
 
// Write data to current position
void GLCD_WriteData(unsigned char dataToWrite)
{                                                        		// Write data to current position
 	dataToWrite = ~dataToWrite;									// Added to support yellow inverted display
    GLCD_BusyWait(screen_x / 64);                        		// Wacht tot GLCD vrij is
    GLCD_DataOutput();
    LCD_EN = 0; Nop();                                       	// EN laag
    LCD_RW = 0; Nop();                                        	// RW laag
    LCD_RS = 1; Nop();                                       	// RS hoog
    GLCD_SendData(dataToWrite);                                	// Data klaarzetten
    GLCD_EnableController(screen_x / 64);                		// CSx laag
 
    GLCD_Delay();
 
    LCD_EN = 1; Nop();                                       	// EN hoog
 
    GLCD_Delay();
 	GLCD_Delay();
 	
    LCD_EN = 0; Nop();                                       	// EN laag
    GLCD_DisableController(screen_x / 64);                		// CSx hoog
    screen_x++;
}
 
//-------------------------------------------------------------------------------------------------
 
unsigned char GLCD_ReadByteFromROMMemory(char *ptr)
{
    return *(ptr);
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_GoTo(unsigned char x, unsigned char y)
{
    unsigned char   i;
    screen_x = x;
    screen_y = y;
	//absx=x;absy=y;
    for (i = 0; i < 3; i++) {
        GLCD_WriteCommand(DISPLAY_SET_Y | 0, i);
        GLCD_WriteCommand(DISPLAY_SET_X | y, i);
        GLCD_WriteCommand(DISPLAY_START_LINE | 0, i);
    }
    GLCD_WriteCommand(DISPLAY_SET_Y | (x % 64), (x / 64));
    GLCD_WriteCommand(DISPLAY_SET_X | y, (x / 64));
}
 
//-------------------------------------------------------------------------------------------------

void GLCD_WriteChar(char charToWrite,unsigned char mode)
{
    int cnt,char_nr;
	char aux=0;	
    char_nr=(int)(charToWrite);
    for(cnt = 0; cnt <6; cnt++)
	{
		aux+=((ASCII_7x5[char_nr][cnt])>>7)&1;
		aux+=((ASCII_7x5[char_nr][cnt])>>5)&2;
		aux+=((ASCII_7x5[char_nr][cnt])>>3)&4;
		aux+=((ASCII_7x5[char_nr][cnt])>>1)&8;
		aux+=((ASCII_7x5[char_nr][cnt])<<1)&16;
		aux+=((ASCII_7x5[char_nr][cnt])<<3)&32;
		aux+=((ASCII_7x5[char_nr][cnt])<<5)&64;
		aux+=((ASCII_7x5[char_nr][cnt])<<7)&128;
		if(mode==0)
		{
			GLCD_WriteData(aux);
		}
		if(mode==1)
		{
        	GLCD_WriteData(255-aux);
		}
		aux=0;
    }
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_WriteString(char *stringToWrite,unsigned char mode)
{
    while (*stringToWrite) {
        GLCD_WriteChar(*stringToWrite++,mode);
    }
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color)
 {
  //color 0 blue
  //color 1 white
  //color 2 toggle
 
    unsigned char   tmp;
    GLCD_GoTo(x, (y / 8));                                	// GLCD_GoTo(18, 3)
    tmp = GLCD_ReadData();                                	// Dummy read
    GLCD_GoTo(x, (y / 8));
    tmp = GLCD_ReadData();                                	// Voorbeeld: tmp = 0b11110000
    GLCD_GoTo(x, (y / 8));                                	// 30 % 8 = 6
    switch (color) 
	{                                        				// (1 << 6) = 0b01000000
	    case 0:                                             // 0 = Bit wissen
	        tmp &= ~(1 << (y % 8));                         // 0b11110000 & 0b10111111 = 0b10110000
	        break;
	    case 1:                                             // 1 = Bit setten
	        tmp |= (1 << (y % 8));
	        break;
	    case 2:                                             // 2 = Bit toggelen
	        tmp ^= (1 << (y % 8));
	        break;
	    default:
	        return;
    }
    GLCD_WriteData(tmp);
}
//-------------------------------------------------------------------------------------------------
 
 
void GLCD_Bitmap(char *bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy,unsigned char mode)
{
    unsigned char   i, j;
    for (j = 0; j < dy / 8; j++) 
	{
    	GLCD_GoTo(x, y + j);
    	for (i = 0; i < dx; i++) 
		{
			if(mode==0)
			{
				GLCD_WriteData(*bmp);
			}
			if(mode==1)
			{
        		GLCD_WriteData(255-*bmp);
			}
    		bmp++;
		}
    }
}
//-------------------------------------------------------------------------------------------------
 
void GLCD_Line(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char color)
{
    int             CurrentX, CurrentY, Xinc, Yinc;
    int             Dx, Dy, TwoDx, TwoDy;
    int             TwoDxAccumulatedError, TwoDyAccumulatedError;
    Dx = (X2 - X1);                                       
    Dy = (Y2 - Y1);                                        
    TwoDx = Dx + Dx;                                        
    TwoDy = Dy + Dy;                                       
    CurrentX = X1;                                      
    CurrentY = Y1;                                        
    Xinc = 1;                    
    Yinc = 1;                     
    if (Dx < 0) {
        Xinc = -1;      
        Dx = -Dx;                                      
        TwoDx = -TwoDx;                                        
    }
    if (Dy < 0) {
        Yinc = -1;                                        
        Dy = -Dy;                                        
        TwoDy = -TwoDy;                                        
    }
    GLCD_SetPixel(X1, Y1, color);                       
    if ((Dx != 0) || (Dy != 0)) {
        if (Dy <= Dx) {
            TwoDxAccumulatedError = 0;                       
            do {
                CurrentX += Xinc;                        
                TwoDxAccumulatedError += TwoDy;                
                if (TwoDxAccumulatedError > Dx) {
                    CurrentY += Yinc;                        
                    TwoDxAccumulatedError -= TwoDx;       
                }
                GLCD_SetPixel(CurrentX, CurrentY, color);        
            } while (CurrentX != X2);                      
        } else {                                        
            TwoDyAccumulatedError = 0;
            do {
                CurrentY += Yinc;                       
                TwoDyAccumulatedError += TwoDx;                
                if (TwoDyAccumulatedError > Dy) {
                    CurrentX += Xinc;
                    TwoDyAccumulatedError -= TwoDy;
                }
                GLCD_SetPixel(CurrentX, CurrentY, color);        
            } while (CurrentY != Y2);
        }
    }
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_Rectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color)
{
    unsigned char   j;
 
    for (j = 0; j < height; j++) { 
		GLCD_SetPixel(x, y + j, color); 
		GLCD_SetPixel(x + width - 1, y + j, color); 
    }
    for (j = 1; j < (width - 1); j++) {
		GLCD_SetPixel(x + j, y, color); 
		GLCD_SetPixel(x + j, y + height - 1, color); 
    }
}
 
//-------------------------------------------------------------------------------------------------
 
void GLCD_Circle(unsigned char cx, unsigned char cy, unsigned char radius, unsigned char color)
{
    int x,y,xchange,ychange,radiusError;
    x = radius;
    y = 0;
    xchange = 1 - 2 * radius;
    ychange = 1;
    radiusError = 0;
    while (x >= y) 
	{
        GLCD_SetPixel(cx + x, cy + y, color);
        GLCD_SetPixel(cx - x, cy + y, color);
        GLCD_SetPixel(cx - x, cy - y, color);
        GLCD_SetPixel(cx + x, cy - y, color);
        GLCD_SetPixel(cx + y, cy + x, color);
        GLCD_SetPixel(cx - y, cy + x, color);
        GLCD_SetPixel(cx - y, cy - x, color);
        GLCD_SetPixel(cx + y, cy - x, color);
        y++;
        radiusError += ychange;
        ychange += 2;
        if ((2 * radiusError + xchange) > 0) 
		{
            x--;
            radiusError += xchange;
            xchange += 2;
        }
    }
}
void GLCD_WriteBigChar(char charToWrite,unsigned char mode)
{
	unsigned char absx,absy;
	absx=screen_x;absy=screen_y;
    int cnt,char_nr,i,j,k,x,y;
	char aux=0;
	if(charToWrite>47&&charToWrite<58){
	k=(int)(charToWrite-47);
	}else
	if(charToWrite==46){k=0;}
	else k=11;
    for(j=0;j<6;j++)
	{
		GLCD_GoTo(absx, absy+j);
		
		for(char_nr=0;char_nr<5;char_nr++)
		{
    		for(cnt = 7; cnt >0; cnt--)
			{
				for(i=7;i>=0;i--)
				{
					aux*=2;
					aux+=((BigNumber[i*5+char_nr+(j*40)+(k*240)])>>cnt)&1;
				}
				if(mode==0)
				{
					GLCD_WriteData(aux);
				}
				if(mode==1)
				{
        			GLCD_WriteData(255-aux);
				}	
				aux=0;
    		}
		}
	}
	GLCD_GoTo(absx, absy);
}
void GLCD_WriteBigString(char *stringToWrite,unsigned char mode)
{
    while (*stringToWrite) {
        GLCD_WriteBigChar(*stringToWrite++,mode);
		GLCD_GoTo(screen_x+35, screen_y);
    }
}