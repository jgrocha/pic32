#include <plib.h>
#include "spi.h"
#include "HardwareProfile.h"

void spiConfig(void)
{
	//Disable SPI interfaces from the devices
	CS_FRAM = 1;		//FRAM	
	CS_CFC = 1;			//Cartão SD
	TMP1CS = 1;			//Termopar 1
	TMP2CS = 1;			//Termopar 2
	HOLD = 1;			
	WP1 = 0;

	//Definitions for all devices except Thermocouple readings
	OpenSPI1(FRAME_ENABLE_OFF | ENABLE_SDO_PIN | SPI_MODE8_ON | SPI_SMP_OFF | SPI_CKE_ON | SLAVE_ENABLE_OFF \
				| CLK_POL_ACTIVE_HIGH | MASTER_ENABLE_ON | SEC_PRESCAL_8_1 | PRI_PRESCAL_64_1, \
				SPI_ENABLE | SPI_IDLE_STOP);
	
}
