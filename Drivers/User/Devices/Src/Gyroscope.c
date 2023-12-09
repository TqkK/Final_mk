/************************************************************************************
 *
 *								[GYROSCOPE - TqK]
 *
 ************************************************************************************/


/*[PRIVATE INCLUDE] -----------------------------------------------------*/
/*_______________________________________________________________________*/
#include "Gyroscope.h"


/*[PRIVATE DEFINE] ------------------------------------------------------*/
/*_______________________________________________________________________*/




/*[PRIVATE DECLARE] -----------------------------------------------------*/
/*_______________________________________________________________________*/

__Spi1_typedef gyroData;

char _gyroTxTmp = 0;

/*
 * ---------------------------- [SUBROUTINES] ----------------------------
 */

int Gyroscope_init()
{
	//--- SPI1 init
	Spi1_init();

	return 0;
}

char Gyroscope_ReadData(char __REG)
{
//	char _data;

	//--- Active slave
	PE3_spi1write(0);

	//--- transmit __REG to slave
	Spi1_txByte(&gyroData, gyroReadCMD(__REG));

	//--- clear dummy data
	Spi1_rxByte(&gyroData);

	//--- enable clock to slave for receive data from it
	Spi1_txByte(&gyroData, 0xFF);

	//--- Read necessary data
	Spi1_rxByte(&gyroData);

	//--- Inactive slave
	PE3_spi1write(1);

	//--- return data
	return gyroData.rxByte;
}

int Gyroscope_WriteData(char __REG, char __DATA)
{
	//--- Active slave
	PE3_spi1write(0);

	//--- transmit __REG to slave
	Spi1_txByte(&gyroData, gyroWriteCMD(__REG));

	//--- clear dummy data
	Spi1_rxByte(&gyroData);

	//--- enable clock to slave for receive data from it
	Spi1_txByte(&gyroData, __DATA);

	//--- clear dummy data
	Spi1_rxByte(&gyroData);

	//--- Inactive slave
	PE3_spi1write(1);

	return 0;
}

/* [For INTERRUPT] __________________________________*/

int Gyroscope_intReadData(char __REG)
{
	gyroData.cmdIndex = gyroReadIndex;

	//--- Active slave
	PE3_spi1write(0);

	//--- transmit __REG to slave
	Spi1_txByte(&gyroData, gyroReadCMD(__REG));

	return 0;
}


int Gyroscope_intWriteData(char __REG, char __DATA)
{
	gyroData.cmdIndex = gyroWriteIndex;
	_gyroTxTmp = __DATA;

	//--- Active slave
	PE3_spi1write(0);

	//--- transmit __REG to slave
	Spi1_txByte(&gyroData, gyroWriteCMD(__REG));

	return 0;
}


void SPI1_IRQHandler()
{
	unsigned int *SR = (unsigned int *)(0x40013008);
	char bitRXNE = bitVALUE(*SR, 0);
//	char bitTXE = bitVALUE(*SR, 1);

	if(bitRXNE && (gyroData.cmdIndex == gyroReadIndex))
	{
		Spi1_intRxByte(&gyroData);

		return;
	}

	if(bitRXNE && (gyroData.cmdIndex == gyroWriteIndex))
	{
		Spi1_intTxByte(&gyroData, _gyroTxTmp);

		return;
	}
}


