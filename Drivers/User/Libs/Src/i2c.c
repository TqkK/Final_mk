/************************************************************************************
 *
 *								[I2C - TqK]
 *
 ************************************************************************************/

/*[PRIVATE INCLUDE] --------------------------------------------------------
 _________________________________________________________________________*/

#include "i2c.h"


/*[PRIVATE DEFINE] ---------------------------------------------------------
 _________________________________________________________________________*/



/*[PRIVATE DECLARE] --------------------------------------------------------
 _________________________________________________________________________*/

unsigned char _i2c1RxByte = 0;

/*
 * [SUBROUTINES] ----------------------------------------------------------
 _________________________________________________________________________*/

/*[GPIO] -----------------------------------------------------------*/

int PB6_i2c1SCLinit()
{
	//--- Enable clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//--- GPIO MODER == alternate function
	unsigned int *MODER = (unsigned int *)(0x40020400);
	bitRST(*MODER, 0b11, 12);
	bitSET(*MODER, 0b10, 12);

	//--- GPIO AFRL == AF04
	unsigned int *AFRL = (unsigned int *)(0x40020420);
	bitRST(*AFRL, 0xF, 24);
	bitSET(*AFRL, 4, 24);

	return 0;
}

int PB9_i2c1SDAinit()
{
	//--- Enable clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//--- GPIO MODER == alternate function
	unsigned int *MODER = (unsigned int *)(0x40020400);
	bitRST(*MODER, 0b11, 18);
	bitSET(*MODER, 0b10, 18);

	//--- GPIO AFRH == AF04
	unsigned int *AFRH = (unsigned int *)(0x40020424);
	bitRST(*AFRH, 0xF, 4);
	bitSET(*AFRH, 4, 4);

	return 0;
}

/*[I2C1] -----------------------------------------------------------*/

int I2C1_init()
{
	//--- SCL init
	PB6_i2c1SCLinit();

	//--- SDA init
	PB9_i2c1SDAinit();

	//--- Enable I2C1 clock
	__HAL_RCC_I2C1_CLK_ENABLE();

	//--- Disable i2c1
	I2C1_disable();

	//--- Set Peripheral clock Frequency is 16mhz
	unsigned int *CR2 = (unsigned int *)(0x40005404);
	bitSET(*CR2, 16, 0);

	//--- Set i2c clock control (SM mode i2c master, Fmcu = 16mhz, Fphe = 200khz)
	/*
	 * Thigh = CCR * TPCLK1 --> CRR = Thigh / TPCLK1 = (200khz)^-1 / (16mhz)^-1 = 80
	 */
	unsigned int *CCR = (unsigned int *)(0x4000541c);
	bitSET(*CCR, 80, 0);

	return 0;
}

int I2C1_enable()
{
	unsigned int *CR1 = (unsigned int *)(0x40005400);
	bitSET(*CR1, 1, 0);

	return 0;
}

int I2C1_disable()
{
	unsigned int *CR1 = (unsigned int *)(0x40005400);
	bitRST(*CR1, 1, 0);

	return 0;
}


int I2C1_masterTransmit(char __addrSLAVE, char __addrREG, unsigned char *__DATA)
{
	unsigned int *SR2 = (unsigned int *)(0x40005418);
	unsigned int *CR1 = (unsigned int *)(0x40005400);
	unsigned int *SR1 = (unsigned int *)(0x40005414);
	unsigned int *DR = (unsigned int *)(0x40005410);

	//--- check BUSY i2c communication
	while(bitVALUE(*SR2, 1));

	//--- Start condition
	bitSET(*CR1, 1, 8);

	//--- Check start condition generated
	while(!bitVALUE(*SR1, 0));

	//--- Send slave address with write indicator to write register address
	*DR = (__addrSLAVE << 1) | cmdI2cWrite;

	//--- Check signal address matched from slave (ADDR bit of i2c_sr1 register)
	while(!bitVALUE(*SR1, 1));

	//--- Clear ADDR bit
	unsigned int _tmpSR2 = *SR2;
	(void)_tmpSR2;

	//--- Send register address what master would read data
	*DR = __addrREG;

	//--- Check transfer data state is succeeded?
	while(!bitVALUE(*SR1, 2));

	//--- Check ACK bit
	while(bitVALUE(*SR1, 10));

	//--- Send data in buffer __DATA and check transfer state, ACK bit
	unsigned int _lengthBuffer = sizeof(__DATA);
	for(int i = 0; i < _lengthBuffer; i++)
	{
		*DR = __DATA[i];

		//--- Check transfered data state
		while(!bitVALUE(*SR1, 2));

		//--- Check ACK bit
		while(bitVALUE(*SR1, 10));
	}

	//--- Stop condition
	bitSET(*CR1, 1, 9);

	return 0;
}

int I2C1_masterReceive(char __addrSLAVE, char __addrREG, char *__retDATA)
{
	unsigned int *SR2 = (unsigned int *)(0x40005418);
	unsigned int *CR1 = (unsigned int *)(0x40005400);
	unsigned int *SR1 = (unsigned int *)(0x40005414);
	unsigned int *DR = (unsigned int *)(0x40005410);

	//--- Check BUSY state i2c communication
	while(bitVALUE(*SR2, 1));

	//--- Start condition
	bitSET(*CR1, 1, 8);

	//--- Check Start condition generated
	while(!bitVALUE(*SR1, 0));

	//--- Send slave address with write indicator to write register address
	*DR = (__addrSLAVE << 1) | cmdI2cWrite;

	//--- Check signal address matched from slave (ADDR bit of i2c_sr1 register)
	while(!bitVALUE(*SR1, 1));


	//--- Clear ADDR bit
	unsigned int _tmpSR2 = *SR2;
	(void)_tmpSR2;

	//--- Send register address what master would read data
	*DR = __addrREG;

	//--- Check transfer data state is succeeded?
	while(!bitVALUE(*SR1, 2));

	//--- Check ACK bit
	while(bitVALUE(*SR1, 10));

	//--- Start condition repeat
	bitSET(*CR1, 1, 8);

	//--- Check start condition generated
	while(!bitVALUE(*SR1, 0));

	//--- Send slave address with read indicator
	*DR = (__addrSLAVE << 1) | cmdI2cRead;

	//--- Check signal address matched from slave (ADDR bit of i2c_sr1 register)
	while(!bitVALUE(*SR1, 1));

	//--- Clear ADDR bit
	_tmpSR2 = *SR2;

	//--- Check received data
//	while(!bitVALUE(*SR1, 6));

	//--- Read data
//	unsigned char _retData = *DR;

	//--- Stop condition
//	bitSET(*CR1, 1, 9);

//	*__retDATA = _retData;
	return 0;
}

/* [DMA 1] -------------------------------------------*/

// [I2C1_rx | Stream 5 | Channel 1] ----------

int I2C1_rxDmaInit(__i2c1_typedef *__i2c1)
{



	//--- Enable clock DMA 1
	__HAL_RCC_DMA1_CLK_ENABLE();

	/*
	 * data receive size == 1
	 * from: I2C1_DR
	 * to: __i2c1->rxByte
	 */
	unsigned int *S5NDTR = (unsigned int *)(0x4002608c);
//	regWRITE(*S5NDTR, 1);
	*S5NDTR = 1;

	unsigned int *S5PAR = (unsigned int *)(0x40026090);
//	regWRITE(*S5PAR, 0x40005410);
	*S5PAR = 0x40005410;

	unsigned int  *S5M0AR = (unsigned int *)(0x40026094);
//	regWRITE(*S5M0AR, __i2c1->rxByte);
//	*S5M0AR = &_i2c1RxByte;
	*S5M0AR = &(__i2c1->rxByte);

	//--- Configure channel 1 of stream 5
	unsigned int *S5CR = (unsigned int *)(0x40026088);
	bitRST(*S5CR, 7, 25);
	bitSET(*S5CR, 1, 25);

	//--- Memory increment mode
	bitSET(*S5CR, 1, 10);

	//--- Circular mode
	bitSET(*S5CR, 1, 8);

	//--- Data transfer direction == peripheral to memory
	bitRST(*S5CR, 2, 6);

	//--- Transfer complete interrupt enable
	bitSET(*S5CR, 1, 4);

	//--- Enable DMA2 str5_ch4 position bit on NVIC ISER	(pos == 16)
	unsigned int *NVIC_ISER0 = (unsigned int *)(0xe000e100);
	bitSET(*NVIC_ISER0, 1, 16);

	//--- Enable DMA 1__Stream 5__Channel 1
	bitSET(*S5CR, 1, 0);

	//--- Enable DMA request for I2C1
	I2C1_rxDMAenable();

	return 0;
}

int I2C1_rxDMAenable()
{
	//--- Enable DMA request for I2C1
	unsigned int *CR2 = (unsigned int *)(0x40005404);
	bitSET(*CR2, 1, 11);

	//--- DMA last transfer
//	bitSET(*CR2, 1, 12);

	return 0;
}

int DMA1_Stream5_ClearPending()
{
	unsigned int *HIFCR = (unsigned int *)(0x4002600c);
	bitSET(*HIFCR, 1, 11);
//	bitSET(*HIFCR, 1, 9);

	return 0;
}

void DMA1_Stream5_IRQHandler()
{
	__asm("NOP");
	DMA1_Stream5_ClearPending();

	//--- Stop condition
	unsigned int *CR1 = (unsigned int *)(0x40005400);
	bitSET(*CR1, 1, 9);
}
