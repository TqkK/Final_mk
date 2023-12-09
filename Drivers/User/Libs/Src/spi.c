/************************************************************************************
 *
 *								[SPI - TqK]
 *
 ************************************************************************************/

/*[PRIVATE INCLUDE] --------------------------------------------------------
 _________________________________________________________________________*/
#include "spi.h"


/*[PRIVATE DEFINE] ---------------------------------------------------------
 _________________________________________________________________________*/
/* To use SPI 1 with interrupt mode */
#define SPI_INTERRUPT

/* To use SPI 1 with DMA mode */
//#define SPI_DMA

#define SS_ACTIVE		PE3_spi1write(1)
#define SS_INACTIVE		PE3_spi1write(0)


/*[PRIVATE DECLARE] --------------------------------------------------------
 _________________________________________________________________________*/


/*
 * [SUBROUTINES] ----------------------------------------------------------
 _________________________________________________________________________*/


/*[SPI1] -----------------------------------------------------------*/

int Spi1_init()
{
	//--- PA5 CLK init
	PA5_spi1CLKinit();

	//--- PA7 MOSI init
	PA7_spi1MOSIinit();

	//--- PA6 MISO init
	PA6_spi1MISOinit();

	//--- PE3 SS init
	PE3_spi1SSinit();
	PE3_spi1write(1);

	//--- Enable SPI1 clock
	__HAL_RCC_SPI1_CLK_ENABLE();

	unsigned int *CR1 = (unsigned int *)(0x40013000);
	//--- [SPI_CR1] Set full duplex
	bitRST(*CR1, 1, 10);

	//--- [SPI_CR1] Set software slave management
	bitSET(*CR1, 1, 9);

	//--- [SPI_CR1] Set Internal slave select
	bitSET(*CR1, 1, 8);

	//--- [SPI_CR1] Frame format - MSB transmitted first
	bitRST(*CR1, 1, 7);

	//--- [SPI_CR1] Baud rate control fPCLK/32	[fPCLK == 16mhz]
	bitRST(*CR1, 0b111, 3);
	bitSET(*CR1, 0b100, 3);

	//--- [SPI_CR1] Master selection
	bitSET(*CR1, 1, 2);

	//--- SPI1 Interrupt enable
#if defined (SPI_INTERRUPT)
	Spi1_interruptInit();
#endif

	//--- [SPI_CR1] SPI enable
	bitSET(*CR1, 1, 6);

	return 0;
}

int Spi1_txByte(__Spi1_typedef *_spi1, char __DATA)
{
	_spi1->txByte = __DATA;
	unsigned int *SR = (unsigned int *)(0x40013008);
	unsigned int *DR = (unsigned int *)(0x4001300c);
	//--- wait SPI is not busy
	while(bitVALUE(*SR, 7));

	//--- wait tx buffer is empty
	while(!bitVALUE(*SR, 1));

	//--- transmit data
	*DR = _spi1->txByte;

	return 0;
}

int Spi1_rxByte(__Spi1_typedef *_spi1)
{
	unsigned int *SR = (unsigned int *)(0x40013008);
	unsigned int *DR = (unsigned int *)(0x4001300c);

	//--- wait SPI is not busy
	while(bitVALUE(*SR, 7));

	//--- wait rx buffer is not empty
	while(!bitVALUE(*SR, 0));

	//--- receive data
	_spi1->rxByte = *DR;

	return 0;
}

/*[SPI1]__INTERRUPT -----------------------------------------------------------*/
#if defined (SPI_INTERRUPT)	//--------------------------------------------------
int Spi1_interruptInit()
{

	//--- TX buffer empty interrupt enable
//	Spi1_interruptTx(1);

	//--- RX buffer not empty interrupt enable
//	Spi1_interruptRx(1);

	unsigned int *NVIC_ISER1 = (unsigned int *)(0xe000e104);
	//--- Enable SPI1 position bit on NVIC ISER	(pos == 35)
	bitSET(*NVIC_ISER1, 1, (35-32));

	return 0;
}

int Spi1_interruptTx(unsigned char __STATE)
{
	unsigned int *CR2 = (unsigned int *)(0x40013004);
	bitRST(*CR2, 1, 7);
	bitSET(*CR2, __STATE, 7);

	return 0;
}

int Spi1_interruptRx(unsigned char __STATE)
{
	unsigned int *CR2 = (unsigned int *)(0x40013004);
	bitRST(*CR2, 1, 6);
	bitSET(*CR2, __STATE, 6);

	return 0;
}


int Spi1_intTxByte(__Spi1_typedef *_spi1, char __DATA)
{
	unsigned int *DR = (unsigned int *)(0x4001300c);
	char _data;

	if(_spi1->cntTx == 0)
	{
		//--- clear dummy data
		_data = *DR;

		//--- enable clock to slave for receive data from it
		_spi1->txByte = __DATA;
		Spi1_txByte(_spi1, _spi1->txByte);

		//--- Increment value
		_spi1->cntTx++;
	}
	else if(_spi1->cntTx > 0)
	{
		//--- clear dummy data
		_data = *DR;

		//--- reset value
		_spi1->cntTx = 0;

		//--- Inactive slave
		PE3_spi1write(1);

		//--- set 1 for spi 1 tx flag done
		_spi1->txFlagDone = 1;
	}

	return 0;
}

int Spi1_intRxByte(__Spi1_typedef *_spi1)
{
	char _data;
	unsigned int *DR = (unsigned int *)(0x4001300c);

	if(_spi1->cntRx == 0)
	{
		//--- clear dummy data
		_data = *DR;

		//--- enable clock to slave for receive data from it
		Spi1_txByte(_spi1, 0xFF);

		//--- Increment value
		_spi1->cntRx++;
	}
	else if(_spi1->cntRx > 0)
	{
		//--- get data
		_spi1->rxByte = *DR;

		//--- reset value
		_spi1->cntRx = 0;

		//--- Inactive slave
		PE3_spi1write(1);

		//--- set 1 for spi 1 rx flag done
		_spi1->rxFlagDone = 1;
	}

	return 0;
}
#endif	//--------------------------------------------------------------------------


/*[SPI1]__DMA -----------------------------------------------------------*/
#if defined (SPI_DMA)	//--------------------------------------------------
int Spi1_DMAinit()
{

	return 0;
}




#endif	//------------------------------------------------------------------


/*[GPIO] -----------------------------------------------------------*/


int PA5_spi1CLKinit()
{
	//--- Enable clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//--- GPIO MODER == alternate function
	unsigned int *MODER = (unsigned int *)(0x40020000);
	bitSET(*MODER, 2, 10);

	//--- GPIO AFRL == AF05
	unsigned int *AFRL = (unsigned int *)(0x40020020);
	bitSET(*AFRL, 5, 20);

	return 0;
}

int PA6_spi1MISOinit()
{
	//--- Enable clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//--- GPIO MODER == alternate function
	unsigned int *MODER = (unsigned int *)(0x40020000);
	bitSET(*MODER, 2, 12);

	//--- GPIO AFRL == AF05
	unsigned int *AFRL = (unsigned int *)(0x40020020);
	bitSET(*AFRL, 5, 24);

	return 0;
}

int PA7_spi1MOSIinit()
{
	//--- Enable clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//--- GPIO MODER == alternate function
	unsigned int *MODER = (unsigned int *)(0x40020000);
	bitSET(*MODER, 2, 14);

	//--- GPIO AFRL == AF05
	unsigned int *AFRL = (unsigned int *)(0x40020020);
	bitSET(*AFRL, 5, 28);

	return 0;
}

int PE3_spi1SSinit()
{
	//--- Enable clock
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//--- GPIO MODER == alternate function
	unsigned int *MODER = (unsigned int *)(0x40021000);
	bitSET(*MODER, 1, 6);

	//--- GPIO OTYPER == push pull
	unsigned int *OTYPER = (unsigned int *)(0x40021004);
	bitRST(*OTYPER, 1, 3);

	//--- GPIO OSPEEDR == medium speed
	unsigned int *OSPEEDR = (unsigned int *)(0x40021008);
	bitSET(*OSPEEDR, 1, 6);

	return 0;
}

int PE3_spi1write(unsigned char __STATE)
{
	unsigned int *ODR = (unsigned int *)(0x40021014);
	bitRST(*ODR, 1, 3);
	bitSET(*ODR, __STATE, 3);

	return 0;
}
