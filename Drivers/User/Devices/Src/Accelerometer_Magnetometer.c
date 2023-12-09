/************************************************************************************
 *
 *							[Accelerometer & Magnetometer - TqK]
 *
 ************************************************************************************/

/*[PRIVATE INCLUDE] --------------------------------------------------------
 _________________________________________________________________________*/

#include "Accelerometer_Magnetometer.h"


/*[PRIVATE DEFINE] ---------------------------------------------------------
 _________________________________________________________________________*/

#define I2C1_DMA

/*[PRIVATE DECLARE] --------------------------------------------------------
 _________________________________________________________________________*/

__i2c1_typedef acceleroData;


/*
 * [SUBROUTINES] ----------------------------------------------------------
 _________________________________________________________________________*/

/*[ACCELEROMETER] -----------------------------------------------------------*/
/*__________________________________________________________________*/

int Accelero_Init()
{
	I2C1_init();
	I2C1_enable();

#if defined (I2C1_DMA)
	I2C1_rxDmaInit(&acceleroData);
#endif

	return 0;
}

int Accelero_WriteData(char __addrSLAVE, char __addrREG, unsigned char *__DATA)
{
	I2C1_masterTransmit(__addrSLAVE, __addrREG, __DATA);
	return 0;
}

int Accelero_ReadData(char __addrSLAVE, char __addrREG, unsigned char *__DATA)
{
	I2C1_masterReceive(__addrSLAVE, __addrREG, __DATA);

	return 0;
}
