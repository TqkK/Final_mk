/************************************************************************************
 *
 *								[GPIO - TqK]
 *
 ************************************************************************************/
#include "gpio.h"
#include "rcc.h"

/*[PD12 - OUTPUT] --------------------------------------------------*/
/*__________________________________________________________________*/
void PD12_outInit()
{
	//--- Enable GPIO D clock
//	__HAL_RCC_GPIOD_CLK_ENABLE();
	GpioClock(GpioD, Enable);

	//--- bitSET GPIO_MODER == output
	unsigned int *moder = (unsigned int *)(0x40020c00);
	bitRST(*moder, 0b11, 24);
	bitSET(*moder, 0b01, 24);

	//--- bitSET GPIO_OTYPER == push-pull
	unsigned int *otyper = (unsigned int *)(0x40020c04);
	bitRST(*otyper, 1, 12);

	//--- bitSET GPIO_OPSEEDR == medium speed
	unsigned int *ospeed = (unsigned int *)(0x40020c08);
	bitRST(*ospeed, 0b11, 24);
	bitSET(*ospeed, 0b01, 24);
}

void PD12_outWrite(unsigned char __STATE)
{
	unsigned int *odr = (unsigned int *)(0x40020c14);
	bitRST(*odr, 0b1, 12);
	bitSET(*odr, __STATE, 12);
}

/*[PA0 - INPUT] --------------------------------------------------*/
/*________________________________________________________________*/
void PA0_inInit()
{
	//--- Enable GPIO A clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//--- bitSET GPIO_MODER == input
	unsigned int *moder = (unsigned int *)(0x40020000);
	bitRST(*moder, 0b11, 0);
	bitSET(*moder, 0b00, 0);

	//--- bitSET GPIO_PUPD == no PUPD
	unsigned int *pupd  = (unsigned int *)(0x4002000c);
	bitRST(*pupd, 0b11, 0);
	bitSET(*pupd, 0b00, 0);
}

unsigned char PA0_state()
{
	unsigned int *idr = (unsigned int *)(0x40020010);
	return bitVALUE(*idr, 0);
}

/*[PB6_PB7 - TX_RX UART1] ------------------------------------------*/
/*__________________________________________________________________*/
void PB6_Uart1txInit()
{
	//--- Enable GPIO B clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//--- GPIO_MODER == alternate function mode
	unsigned int *moder = (unsigned int *)(0x40020400);
	bitRST(*moder, 0b11, 12);
	bitSET(*moder, 0b10, 12);

	//--- GPIO_AFRL == AF07
	unsigned int *afrl = (unsigned int *)(0x40020420);
	bitRST(*afrl, 0x0F, 24);
	bitSET(*afrl, 7, 24);
}

void PB7_Uart1rxInit()
{
	//--- Enable GPIO B clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//--- GPIO_MODER == alternate function mode
	unsigned int *moder = (unsigned int *)(0x40020400);
	bitRST(*moder, 0b11, 14);
	bitSET(*moder, 0b10, 14);

	//--- GPIO_AFRL == AF07
	unsigned int *afrl = (unsigned int *)(0x40020420);
	bitRST(*afrl, 0x0F, 28);
	bitSET(*afrl, 7, 28);
}
