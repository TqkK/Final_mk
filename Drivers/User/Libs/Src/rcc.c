/************************************************************************************
 *
 *										[RCC - TqK]
 *
 ************************************************************************************/

/*
 * INCLUDES ------------------------------------------------------------------
 _____________________________________________________________________________*/
#include "Rcc.h"

#define __RCC_VALUE		01

/*
 * VARIABLES ------------------------------------------------------------------
 _____________________________________________________________________________*/



/*
 * FUNCTIONS ------------------------------------------------------------------
 _____________________________________________________________________________*/

/*
 * @Brief	: Set up RCC to generate a clock from HSE (8Mhz)
 * @Param	: /__PLLM, x__PLLN, /__PLLP
 * @Retval	: None
 */
#if (__RCC_VALUE == 0)
int Rcc_Init(unsigned char __PLLM, unsigned short __PLLN, unsigned char __PLLP)
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	unsigned int *RCC_PLLCFGR = (unsigned int *)(RCC_AddBase + PLLCFGR);
	unsigned int *RCC_CFGR = (unsigned int *)(RCC_AddBase + CFGR);

	//--- Disable PLL
	bitRST(*RCC_CR, 1, 24);

	//--- Enable HSE and wait HSE ready
	bitSET(*RCC_CR, 1, 16);
	while(!bitVALUE(*RCC_CR, 17));

	//--- set M div = /8
	bitRST(*RCC_PLLCFGR, 0b111111, 0);
	bitSET(*RCC_PLLCFGR, 8, 0);


	//--- set N mul = 32
	bitRST(*RCC_PLLCFGR, 0b111111111, 6);
	bitSET(*RCC_PLLCFGR, 32, 6);


	//--- set P div = 2
	bitRST(*RCC_PLLCFGR, 0b11, 16);
	bitSET(*RCC_PLLCFGR, 0, 16);

	//--- set PLL source is HSE
	bitSET(*RCC_PLLCFGR, 1, 22);


	//--- Enable PLL and wait PLL ready
	bitSET(*RCC_CR, 1, 24);
	while(!bitVALUE(*RCC_CR, 25));

	//--- Select system clock in PLL
	bitSET(*RCC_CFGR, 0b10, 0);
	while(!(((*RCC_CFGR >> 2) & 0b11) == 0b10));

	unsigned int *FLASH_ACR = (unsigned int *)(0x40023c00);
	bitSET(*FLASH_ACR, 0, 0);



	return 0;
}

#endif

#if (__RCC_VALUE == 1)
int Rcc_Init(unsigned char __PLLM, unsigned short __PLLN, unsigned char __PLLP)
{
	//--- Disable PLL
	PLL_Disable();

	//--- Enable HSE
	HSE_Enable();

	//--- set M div = /8
	PLL_setPLLM(8);

	//--- set N mul = 32
	PLL_setPLLN(32);

	//--- set P div = 2
	PLL_setPLLP(0);

	//--- set PLL source is HSE
	PLL_SRC(PllSrc_HSE);



	//--- Enable PLL and wait PLL ready
	PLL_Enable();

	//--- Select system clock in PLL
	SysClockSwitch(SysSrc_PLL);

	FlashAccessTime(0);


	return 0;
}
#endif

/*
 * @Brief	: Disable PLL
 */
int PLL_Disable()
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	bitRST(*RCC_CR, 1, 24);

	return 0;
}

/*
 * @Brief	: Enable PLL
 */
int PLL_Enable()
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	bitSET(*RCC_CR, 1, 24);

	while(!bitVALUE(*RCC_CR, 25));

	return 0;
}

/*
 * @Brief	: Entry clock source for PLL
 */
int PLL_SRC(PllSrc_Typedef __SRCCLK)
{
	if((__SRCCLK < PllSrc_HSI) || (__SRCCLK > PllSrc_HSE))
	{
		return -1;
	}

	unsigned int *RCC_PLLCFGR = (unsigned int *)(RCC_AddBase + PLLCFGR);
	bitRST(*RCC_PLLCFGR, 1, 22);

	bitSET(*RCC_PLLCFGR, __SRCCLK, 22);

	return 0;
}

/*
 * @Brief	: Set PLLM
 */
int PLL_setPLLM(unsigned char __PLLM)
{
	if((__PLLM < 2) || (__PLLM > 63))
	{

		return -1;
	}

	unsigned int *RCC_PLLCFGR = (unsigned int *)(RCC_AddBase + PLLCFGR);
	bitRST(*RCC_PLLCFGR, 0b111111, 0);

	bitSET(*RCC_PLLCFGR, __PLLM, 0);

	return 0;
}

/*
 * @Brief	: Set PLLN
 */
int PLL_setPLLN(unsigned short __PLLN)
{
	if((__PLLN < 2) || (__PLLN > 432))
	{

		return -1;
	}

	unsigned int *RCC_PLLCFGR = (unsigned int *)(RCC_AddBase + PLLCFGR);
	bitRST(*RCC_PLLCFGR, 0b111111111, 6);

	bitSET(*RCC_PLLCFGR, __PLLN, 6);

	return 0;
}

/*
 * @Brief	: Set PLLP
 */
int PLL_setPLLP(unsigned char __PLLP)
{
	if((__PLLP < 0) || (__PLLP > 3))
	{

		return -1;
	}

	unsigned int *RCC_PLLCFGR = (unsigned int *)(RCC_AddBase + PLLCFGR);
	bitRST(*RCC_PLLCFGR, 0b11, 16);

	bitSET(*RCC_PLLCFGR, __PLLP, 16);

	return 0;
}

/*
 * @Brief	: Set system clock switch
 */
int SysClockSwitch(SysSrc_Typedef __SRCCLK)
{
	unsigned int *RCC_CFGR = (unsigned int *)(RCC_AddBase + CFGR);
	bitRST(*RCC_CFGR, 0b11, 0);

	bitSET(*RCC_CFGR, __SRCCLK, 0);

	while(!(((*RCC_CFGR >> 2) & 0b11) == __SRCCLK));

	return 0;
}

/*
 * @Brief	: Enable HSE
 */
int HSE_Enable()
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	bitSET(*RCC_CR, 1, 16);

	while(!bitVALUE(*RCC_CR, 17));

	return 0;
}

/*
 * @Brief	: Disable HSE
 */
int HSE_Disable()
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	bitRST(*RCC_CR, 1, 16);

	return 0;
}

/*
 * @Brief	: Enable HSI
 */
int HSI_Enable()
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	bitSET(*RCC_CR, 1, 0);

	while(!bitVALUE(*RCC_CR, 1));

	return 0;
}

/*
 * @Brief	: Disable HSI
 */
int HSI_Disable()
{
	unsigned int *RCC_CR = (unsigned int *)(RCC_AddBase + CR);
	bitRST(*RCC_CR, 1, 0);

	return 0;
}

/*
 * @Brief	: Flash memory access time
 */
int FlashAccessTime(unsigned char __WAITSTATE)
{
	unsigned int *FLASH_ACR = (unsigned int *)(0x40023c00);
	bitRST(*FLASH_ACR, 0x0F, 0);

	bitSET(*FLASH_ACR, __WAITSTATE, 0);

	return 0;
}


// [GPIO CLOCK SET UP] --------------------------------------------

int GpioClock(GpioClock_Typdef __GPIO, Ctrl_Typedef __STATE)
{
	unsigned int *RCC_AHB1ENR = (unsigned int *)(RCC_AddBase + AHB1ENR);

	bitRST(*RCC_AHB1ENR, 1, __GPIO);

	bitSET(*RCC_AHB1ENR, __STATE, __GPIO);

	return 0;
}


// [DMA CLOCK SET UP] --------------------------------------------
int DmaClock(DmaClock_Typedef __DMA, Ctrl_Typedef __STATE)
{
	unsigned int *RCC_AHB1ENR = (unsigned int *)(RCC_AddBase + AHB1ENR);
	bitRST(*RCC_AHB1ENR, 1, __DMA);

	bitSET(*RCC_AHB1ENR, __STATE, __DMA);

	return 0;
}

// [CRC CLOCK SET UP] --------------------------------------------
int CrcClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_AHB1ENR = (unsigned int *)(RCC_AddBase + AHB1ENR);
	bitRST(*RCC_AHB1ENR, 1, 12);

	bitSET(*RCC_AHB1ENR, __STATE, 12);

	return 0;
}

// [USB OTG CLOCK SET UP] --------------------------------------------
int UsbOtgClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_AHB2ENR = (unsigned int *)(RCC_AddBase + AHB2ENR);
	bitRST(*RCC_AHB2ENR, 1, 7);

	bitSET(*RCC_AHB2ENR, __STATE, 7);
	return 0;
}

// [TIMER CLOCK SET UP] --------------------------------------------
int TimerClock(TimerClock_Typedef __TIM, Ctrl_Typedef __STATE)
{
	if(__TIM >= TIMER1)
	{
		unsigned int *RCC_APB2ENR = (unsigned int *)(RCC_AddBase + APB2ENR);
		bitRST(*RCC_APB2ENR, 1, (__TIM - TIMER1));

		bitSET(*RCC_APB2ENR, __STATE, (__TIM - TIMER1));

		return 0;
	}

	unsigned int *RCC_APB1ENR = (unsigned int *)(RCC_AddBase + APB1ENR);
	bitRST(*RCC_APB1ENR, 1, (__TIM));

	bitSET(*RCC_APB1ENR, __STATE, (__TIM));

	return 0;
}

// [USART CLOCK SET UP] --------------------------------------------
int UsartClock(UsartClock_Typdef __USART, Ctrl_Typedef __STATE)
{
	if(__USART == Usart2)
	{
		unsigned int *RCC_APB1ENR = (unsigned int *)(RCC_AddBase + APB1ENR);
		bitRST(*RCC_APB1ENR, 1, (__USART));

		bitSET(*RCC_APB1ENR, __STATE, (__USART));
		return 0;
	}

	unsigned int *RCC_APB2ENR = (unsigned int *)(RCC_AddBase + APB2ENR);
	bitRST(*RCC_APB2ENR, 1, __USART);

	bitSET(*RCC_APB2ENR, __STATE, __USART);
	return 0;
}

// [I2C CLOCK SET UP] --------------------------------------------
int I2cClock(I2cClock_Typedef __I2C, Ctrl_Typedef __STATE)
{
	unsigned int *RCC_APB1ENR = (unsigned int *)(RCC_AddBase + APB1ENR);
	bitRST(*RCC_APB1ENR, 1, (__I2C));

	bitSET(*RCC_APB1ENR, __STATE, (__I2C));
	return 0;
}

// [SPI CLOCK SET UP] --------------------------------------------
int SpiClock(SpiClock_Typedef __SPI, Ctrl_Typedef __STATE)
{
	if((__SPI == Spi2) || (__SPI == Spi3))
	{
		unsigned int *RCC_APB1ENR = (unsigned int *)(RCC_AddBase + APB1ENR);
		bitRST(*RCC_APB1ENR, 1, (__SPI));

		bitSET(*RCC_APB1ENR, __STATE, (__SPI));
		return 0;
	}

	unsigned int *RCC_APB2ENR = (unsigned int *)(RCC_AddBase + APB2ENR);
	bitRST(*RCC_APB2ENR, 1, __SPI);

	bitSET(*RCC_APB2ENR, __STATE, __SPI);

	return 0;
}


// [WWDG CLOCK SET UP] --------------------------------------------
int WwdgClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_APB1ENR = (unsigned int *)(RCC_AddBase + APB1ENR);
	bitRST(*RCC_APB1ENR, 1, 11);

	bitSET(*RCC_APB1ENR, __STATE, 11);
	return 0;
}

// [PWR CLOCK SET UP] --------------------------------------------
int PwrClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_APB1ENR = (unsigned int *)(RCC_AddBase + APB1ENR);
	bitRST(*RCC_APB1ENR, 1, 28);

	bitSET(*RCC_APB1ENR, __STATE, 28);
	return 0;
}

// [ADC CLOCK SET UP] --------------------------------------------
int AdcClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_APB2ENR = (unsigned int *)(RCC_AddBase + APB2ENR);
	bitRST(*RCC_APB2ENR, 1, 8);

	bitSET(*RCC_APB2ENR, __STATE, 8);
	return 0;
}

// [SDIO CLOCK SET UP] --------------------------------------------
int SdioClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_APB2ENR = (unsigned int *)(RCC_AddBase + APB2ENR);
	bitRST(*RCC_APB2ENR, 1, 11);

	bitSET(*RCC_APB2ENR, __STATE, 1);
	return 0;
}

// [SYSCFG CLOCK SET UP] --------------------------------------------
int SysCfgClock(Ctrl_Typedef __STATE)
{
	unsigned int *RCC_APB2ENR = (unsigned int *)(RCC_AddBase + APB2ENR);
	bitRST(*RCC_APB2ENR, 1, 14);

	bitSET(*RCC_APB2ENR, __STATE, 14);
	return 0;
}
