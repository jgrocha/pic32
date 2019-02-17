#ifndef _RTC_H_
#define	_RTC_H_

#define INT_RTC_TRIS		TRISEbits.TRISE8

/**************************/
/* RTC REGISTER ADDRESSES */
/**************************/
#define SECONDS_ADDR 	0x00
#define MINUTES_ADDR 	0x01
#define HOURS_ADDR		0x02
#define DAYOFWEEK_ADDR	0x03
#define DAY_ADDR 		0x04
#define MONTH_ADDR	 	0x05
#define YEAR_ADDR 		0x06
#define A1SEC_ADDR		0x07
#define	A1MIN_ADDR		0x08
#define	A1HOUR_ADDR		0x09
#define	A1DAY_ADDR 		0x0A
#define	A2MIN_ADDR		0x0B
#define	A2HOUR_ADDR		0x0C
#define	A2DAY_ADDR		0x0D
#define CONTROL_ADDR	0x0E
#define STATUS_ADDR		0x0F
#define	TRICKLE_ADDR	0x10

#define	ALARM1FLAG		1
#define ALARM2FLAG		2

/*************************/
/* Structures definition */
/*************************/
typedef union
{
	unsigned char reg;
	struct
	{
		unsigned seconds	: 4;
		unsigned seconds10	: 3;
		unsigned bit7		: 1;	
	};
} SECONDS;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned minutes	: 4;
		unsigned minutes10	: 3;
		unsigned bit7		: 1;
	};
} MINUTES;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned hour		: 4;
		unsigned hour10		: 2;
		unsigned format		: 1;
		unsigned bit7		: 1;
	};
} HOURS;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned day		: 3;
		unsigned bit3		: 1;
		unsigned bit4		: 1;
		unsigned bit5		: 1;
		unsigned bit6		: 1;
		unsigned bit7		: 1;		
	};
} DAYOFWEEK;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned day		: 4;
		unsigned day10		: 2;
		unsigned bit6		: 1;
		unsigned bit7		: 1;		
	};
} DAY;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned month		: 4;
		unsigned month10	: 1;
		unsigned bit5		: 1;
		unsigned bit6		: 1;
		unsigned century	: 1;
	};
} MONTH;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned year		: 4;
		unsigned year10		: 4;
	};
} YEAR;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned seconds	: 4;
		unsigned seconds10	: 3;
		unsigned a1m1		: 1;
	};
} ALARM1SEC;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned minutes	: 4;
		unsigned minutes10	: 3;
		unsigned a1m2		: 1;
	};
} ALARM1MIN;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned hour		: 4;
		unsigned hour10		: 2;
		unsigned format		: 1;
		unsigned a1m3		: 1;
	};
} ALARM1HOUR;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned date		: 4;
		unsigned date10		: 2;
		unsigned dt			: 1;
		unsigned a1m4		: 1;
	};
} ALARM1DATE;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned minutes	: 4;
		unsigned minutes10	: 3;
		unsigned a1m2		: 1;
	};
} ALARM2MIN;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned hour		: 4;
		unsigned hour10		: 2;
		unsigned format		: 1;
		unsigned a1m3		: 1;
	};
} ALARM2HOUR;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned date		: 4;
		unsigned date10		: 2;
		unsigned dt			: 1;
		unsigned a1m4		: 1;
	};
} ALARM2DATE;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned a1ie		: 1;
		unsigned a2ie		: 1;
		unsigned intcn		: 1;
		unsigned rs1		: 1;
		unsigned rs2		: 1;
		unsigned bbsqi		: 1;
		unsigned bit6		: 1;
		unsigned eosc		: 1;
	};
} CONTROL;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned a1if		: 1;
		unsigned a2if		: 1;
		unsigned bit2		: 1;
		unsigned bit3		: 1;
		unsigned bit4		: 1;
		unsigned bit5		: 1;
		unsigned bit6		: 1;
		unsigned osf		: 1;
	};
} STATUS;

typedef union
{
	unsigned char reg;
	struct
	{
		unsigned ROUT0		: 1;
		unsigned ROUT1		: 1;
		unsigned DS0		: 1;
		unsigned DS1		: 1;
		unsigned TCS0		: 1;
		unsigned TCS1		: 1;
		unsigned TCS2		: 1;
		unsigned TCS3		: 1;
	};
} TRICKLE_CHARGER;

typedef	struct
{
	SECONDS		seconds;
	MINUTES		minutes;
	HOURS		hours;
	DAYOFWEEK	dayOfWeek;
	DAY			day;
	MONTH		month;
	YEAR		year;
	ALARM1SEC	alarm1sec;
	ALARM1MIN	alarm1min;
	ALARM1HOUR	alarm1hour;
	ALARM1DATE	alarm1date;
	ALARM2MIN	alarm2min;
	ALARM2HOUR	alarm2hour;
	ALARM2DATE	alarm2date;
	CONTROL		control;
	STATUS		status;
	TRICKLE_CHARGER	trickle_charger;
} RTC;

typedef struct
{
	unsigned char hours;
	unsigned char minutes;
	unsigned char seconds;
} TIME;

typedef struct
{
	unsigned char dayOfWeek;
	unsigned char day;
	unsigned char month;
	unsigned int year;
} DATE;

/***********************/
/* Function Prototypes */
/***********************/

/************************************************************
Function name:	rtcConfig
Description:	rtc configuration
Parameter:		none
Return Value:	none
************************************************************/
void rtcConfig(void);


/************************************************************
Function name:	rtcRead
Description:	read time from RTC (seconds, minutes, hour, 
					day of week, day, month, year)
Parameter:		none
Return Value:	none
************************************************************/
void rtcRead(void);

/***************************************************************
Function name	: rtcUpdate
Description		: update rtc time
Parameters		: hour, minute, second, day, date, month, year
Return Value	: none
***************************************************************/
void rtcUpdate(unsigned char hour, unsigned char minute, unsigned char second, unsigned char day, unsigned char date, unsigned char month, unsigned char year);

/************************************************************
Function name:	rtcWriteReg
Description:	write data to rtc register addrMem
Parameter:		addrMem - rtc register address
				data	- data to be written
Return Value:	none
************************************************************/
void rtcWriteReg(unsigned char addrMem, unsigned char data);

/************************************************************
Function name:	rtcReadReg
Description:	read data from rtc register addrMem
Parameter:		addrMem - rtc register address
Return Value:	unsigned char - data read
************************************************************/
unsigned char rtcReadReg(unsigned char addrMem);

/************************************************************
Function name:	rtcClearAlarmFlag
Description:	clear alarm flag
Parameter:		alarmFlag - select which alarm flag to clear
Return Value:	none
************************************************************/
void rtcClearAlarmFlag(unsigned char alarmFlag);

/************************************************************
Function name:	rtcCheckValidity
Description:	check number of days of a month
Parameter:		m	- month
				y	- year
Return Value:	number of days of a month
************************************************************/
unsigned char rtcCheckValidity(unsigned char m, unsigned char y);

void rtcPrintTimeDate(void);

#endif
